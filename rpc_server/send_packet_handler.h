#pragma once

namespace fasci_rpc {
namespace server {
namespace impl {
	

/**
 * ������Ӧ���ݰ����첽����
 */
class ISendPacketHandler {
public:
	virtual ~ISendPacketHandler() = 0;

	/**
	 * �첽������Ӧ��
	 * @param socket				�׽���
	 * @param status_code			״̬��
	 * @param data					��Ӧ���ݣ�����״̬��ΪSUCCESSʱΪ��Ч
	 * @param size					���ݴ�С
	 * @param complete_callback		�첽�������ʱ���ص�
	 */
	virtual void asyncSend(
		std::shared_ptr<boost::asio::ip::tcp::socket> socket,
		unsigned int status_code,
		std::shared_ptr<char> data,
		size_t size,
		std::function<void ()> complete_callback) = 0;
};

/**
 * ISendPacketFactory�Ĵ�������
 */
class SendPacketHandlerFactory {
public:
	std::shared_ptr<ISendPacketHandler> create();
};


} // namespace impl
} // namespace server
} // namespace fasci_rpc