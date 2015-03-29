#include "stdafx.h"

#include "../common/packet_header.h"
#include "../common/status_code.h"
#include "receive_packet_handler.h"

using namespace std;
using namespace boost::asio;
using namespace boost::asio::ip;
using namespace fasci_rpc::server;
using namespace fasci_rpc::common;
using namespace fasci_rpc::server::impl;


IReceivePacketHandler::~IReceivePacketHandler() {
}

class ReceivePacketHandler : public IReceivePacketHandler {
public:
	/* override */
	void asyncReceive(
		shared_ptr<tcp::socket> socket, 
		function<void (unsigned int status_code, shared_ptr<char> packet_data, size_t packet_size)> complete_callback) {
			shared_ptr<RequestHeader> packet_header(new RequestHeader());
			using boost::system::error_code;
			async_read(*socket, buffer(packet_header.get(), sizeof(RequestHeader)), [=](const error_code& error, size_t bytes) {
				if (!error) {
					if (packet_header->size <= REQUEST_PACKET_SIZE_LIMIT) {
						using boost::system::error_code;
						shared_ptr<char> packet_data(new char[packet_header->size]);
						async_read(*socket, buffer(packet_data.get(), packet_header->size), [=](const error_code& error, size_t bytes) {
							if (!error) {
								complete_callback(SUCCESS, packet_data, packet_header->size);
							}
						});
					} else {
						complete_callback(PACKET_SIZE_TOO_LARGE, nullptr, 0);
					}
				}
			});
	}
};

std::shared_ptr<IReceivePacketHandler> ReceivePacketHandlerFactory::create() {
	return std::shared_ptr<IReceivePacketHandler>(new ReceivePacketHandler());
}