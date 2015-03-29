#include "stdafx.h"

#include <vector>

#include "../common/packet_header.h"
#include "../common/status_code.h"
#include "send_packet_handler.h"

using namespace std;
using namespace boost::asio;
using namespace boost::asio::ip;
using namespace fasci_rpc::server;
using namespace fasci_rpc::common;
using namespace fasci_rpc::server::impl;


class SendPacketHandler : public ISendPacketHandler {
public:
	/* override */
	void asyncSend(
		shared_ptr<tcp::socket> socket,
		unsigned int status_code,
		shared_ptr<char> data,
		size_t size,
		function<void ()> complete_callback) {
			std::shared_ptr<ResponseHeader> packet_header(new ResponseHeader());
			packet_header->status = status_code;
			packet_header->size = status_code == SUCCESS ? size : 0;

			vector<const_buffer> bv;
			bv.push_back(buffer(packet_header.get(), sizeof(ResponseHeader)));
			bv.push_back(buffer(data.get(), size));

			using boost::system::error_code;
			async_write(*socket, bv, [=](const error_code& error, size_t bytes) {
				if (!error) {
					complete_callback();
				}
			});
	}
};

ISendPacketHandler::~ISendPacketHandler() {
}

shared_ptr<ISendPacketHandler> SendPacketHandlerFactory::create() {
	return shared_ptr<ISendPacketHandler>(new SendPacketHandler());
}