#pragma once

#include "thread_pool.h"
#include "service_object.h"
#include "service_object_factory.h"
#include "request_handler.h"

namespace fasci_rpc {
namespace server {


/**
 * RPC服务端，依赖于boost::asio库
 */
class RpcServer : private boost::noncopyable {
public:
	RpcServer(boost::asio::io_service& io_service);

	~RpcServer();

public:
	/**
	 * 注册IServiceObject生成工厂
	 */
	void registerServiceFactory(std::shared_ptr<IServiceObjectFactory> factory) { _service_factory = factory; }

	/**
	 * 初始化并开始运行，此函数立即返回
	 */
	void init(const char* ip, unsigned short port, size_t threads);

private:
	boost::asio::io_service& _io_service;
	std::shared_ptr<boost::asio::ip::tcp::acceptor> _acceptor;
	utility::ThreadPool _thread_pool;
	std::shared_ptr<IServiceObjectFactory> _service_factory;

	void asyncAccept();
	void asyncProcessRequest(std::shared_ptr<impl::Session> socket);
};


} // namespace server
} // namespace fasci_rpc

