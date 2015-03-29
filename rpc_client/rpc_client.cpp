#include "stdafx.h"

#include "rpc_client.h"

using namespace std;
using namespace boost::archive;
using namespace boost::asio::ip;
using namespace fasci_rpc::client;

RpcClient::RpcClient(boost::asio::io_service& io_service) : _io_service(io_service) {
}

RpcClient::~RpcClient() {
}

void RpcClient::init(const char* ip, unsigned short port) {
	_socket.reset(new tcp::socket(_io_service));
	tcp::endpoint server_endpoint(address::from_string(ip), port);
	_socket->connect(server_endpoint);
}

shared_ptr<ServiceProxy> RpcClient::createServiceProxy(const string& name) {
	return shared_ptr<ServiceProxy>(new ServiceProxy(name, _socket));
}