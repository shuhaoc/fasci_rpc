#pragma once

namespace fasci_rpc {
namespace server {
namespace impl {


/**
 * �������ݰ����첽����
 */
class IReceivePacketHandler {
public:
	virtual ~IReceivePacketHandler() = 0;

	/**
	 * �첽��������
	 * @param socket				�׽���
	 * @param complete_callback		�첽�������ʱ�����ã������ֱ�Ϊ״̬�롢���յ������ݡ����ݴ�С
	 */
	virtual void asyncReceive(std::shared_ptr<boost::asio::ip::tcp::socket> socket, 
		std::function<void (unsigned int, std::shared_ptr<char>, size_t)> complete_callback) = 0;
};

/**
 * IReceivePacketHandler�Ĵ�������
 */
class ReceivePacketHandlerFactory {
public:
	std::shared_ptr<IReceivePacketHandler> create();
};


} // namespace impl
} // namespace server
} // namespace fasci_rpc