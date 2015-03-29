#pragma once

#include "service_proxy.h"

namespace fasci_rpc {
namespace client {

/**
 * RPC¿Í»§¶Ë
 */
class RpcClient : private boost::noncopyable {
public:
	RpcClient(boost::asio::io_service& io_service);

	~RpcClient();

public:
	void init(const char* ip, unsigned short port);

	std::shared_ptr<ServiceProxy> createServiceProxy(const std::string& name);

private:
	boost::asio::io_service& _io_service;
	std::shared_ptr< boost::asio::ip::tcp::socket> _socket;
};

} // namespace client 
} // namespace fasci_rpc 