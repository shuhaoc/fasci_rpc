#pragma once

namespace fasci_rpc {
namespace server {
namespace impl {


/**
 * 负责数据包的异步接收
 */
class IReceivePacketHandler {
public:
	virtual ~IReceivePacketHandler() = 0;

	/**
	 * 异步接受数据
	 * @param socket				套接字
	 * @param complete_callback		异步接受完成时被调用，参数分别为状态码、接收到的数据、数据大小
	 */
	virtual void asyncReceive(std::shared_ptr<boost::asio::ip::tcp::socket> socket, 
		std::function<void (unsigned int, std::shared_ptr<char>, size_t)> complete_callback) = 0;
};

/**
 * IReceivePacketHandler的创建工厂
 */
class ReceivePacketHandlerFactory {
public:
	std::shared_ptr<IReceivePacketHandler> create();
};


} // namespace impl
} // namespace server
} // namespace fasci_rpc