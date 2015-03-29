#pragma once

#include <map>

#include "service_object.h"

namespace fasci_rpc {
namespace server {
namespace impl {


/**
 * 服务端会话存储
 */
struct Session {
	std::shared_ptr<boost::asio::ip::tcp::socket> socket;
	std::map<std::string, std::shared_ptr<IServiceObject> > services;
};


} // namespace impl
} // namespace server
} // namespace fasci_rpc