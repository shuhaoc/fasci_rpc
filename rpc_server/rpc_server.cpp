#include "stdafx.h"

#include "../common/packet_header.h"
#include "../common/status_code.h"
#include "receive_packet_handler.h"
#include "send_packet_handler.h"
#include "session.h"
#include "service_object_factory.h"
#include "rpc_server.h"

using namespace std;
using namespace boost::asio;
using namespace boost::asio::ip;
using namespace fasci_rpc::server;
using namespace fasci_rpc::common;
using namespace fasci_rpc::server::impl;
using namespace fasci_rpc::server::utility;

static const size_t REQUEST_SIZE_LIMIT = 1 << 13;

RpcServer::RpcServer(boost::asio::io_service& io_service) : _io_service(io_service) {
}

RpcServer::~RpcServer() {
}

void RpcServer::init(const char* ip, unsigned short port, size_t threads) {
	_thread_pool.init(threads);

	tcp::endpoint listen_endpoint(ip::address::from_string(ip), port);
	_acceptor = std::shared_ptr<tcp::acceptor>(new tcp::acceptor(_io_service, listen_endpoint));
	asyncAccept();
}

void RpcServer::asyncAccept() {
	shared_ptr<tcp::socket> peer_socket(new tcp::socket(_acceptor->get_io_service()));
	shared_ptr<tcp::endpoint> peer_endpoint(new tcp::endpoint());

	using boost::system::error_code;
	_acceptor->async_accept(*peer_socket, *peer_endpoint, [=](const error_code& error) {
		if (!error) {
			peer_endpoint;			// 历经数小时的调试，起死回生的一句代码，只为延续peer_endpoint的存在
			shared_ptr<Session> session(new Session());
			session->socket = peer_socket;
			session->services = _service_factory->create();
			asyncProcessRequest(session);
			asyncAccept();
		}
	});
}

void RpcServer::asyncProcessRequest(std::shared_ptr<Session> session) {
	ReceivePacketHandlerFactory().create()->asyncReceive(
		session->socket, [=](unsigned int status_code, shared_ptr<char> packet_data, size_t packet_size) {
			if (status_code == SUCCESS) {
				_thread_pool.addTask([=]() {
					shared_ptr<char> response_data;
					size_t response_size;
					unsigned int status = RequestHandlerFactory().create()->process(
						session, packet_data, packet_size, response_data, response_size);
					SendPacketHandlerFactory().create()->asyncSend(
						session->socket, status, response_data, response_size, [=]() {
							asyncProcessRequest(session);
						}
					);
				});
			}
		}
	);
}