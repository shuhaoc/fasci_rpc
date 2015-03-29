#pragma once

#include "session.h"

namespace fasci_rpc {
namespace server {
namespace impl {


/**
 * ��������������
 */
class IRequestHandler {
public:
	virtual ~IRequestHandler() { };

	/**
	 * ��������
	 * @param session			�Ự
	 * @param request_data		�����������������
	 * @param request_size		����������������ݴ�С
	 * @param response_data		�����������Ӧ����
	 * @param response_size		�����������Ӧ���ݴ�С
	 * @return					״̬��
	 */
	virtual unsigned int process(
		std::shared_ptr<Session> session,
		std::shared_ptr<char> request_data, 
		size_t request_size,
		std::shared_ptr<char>& response_data, 
		size_t& response_size) = 0;
};


/**
 * IRequestHandler�Ĵ�������
 */
class RequestHandlerFactory {
public:
	std::shared_ptr<IRequestHandler> create();
};


} // namespace impl
} // namespace server
} // namespace fasci_rpc