#pragma once

namespace fasci_rpc {
namespace server {
namespace impl {
	

/**
 * 负责响应数据包的异步发送
 */
class ISendPacketHandler {
public:
	virtual ~ISendPacketHandler() = 0;

	/**
	 * 异步发送响应包
	 * @param socket				套接字
	 * @param status_code			状态码
	 * @param data					响应数据，仅在状态码为SUCCESS时为有效
	 * @param size					数据大小
	 * @param complete_callback		异步发送完成时被回调
	 */
	virtual void asyncSend(
		std::shared_ptr<boost::asio::ip::tcp::socket> socket,
		unsigned int status_code,
		std::shared_ptr<char> data,
		size_t size,
		std::function<void ()> complete_callback) = 0;
};

/**
 * ISendPacketFactory的创建工厂
 */
class SendPacketHandlerFactory {
public:
	std::shared_ptr<ISendPacketHandler> create();
};


} // namespace impl
} // namespace server
} // namespace fasci_rpc