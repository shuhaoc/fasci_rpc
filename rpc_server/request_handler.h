#pragma once

#include "session.h"

namespace fasci_rpc {
namespace server {
namespace impl {


/**
 * 负责处理请求数据
 */
class IRequestHandler {
public:
	virtual ~IRequestHandler() { };

	/**
	 * 处理数据
	 * @param session			会话
	 * @param request_data		输入参数，请求数据
	 * @param request_size		输入参数，请求数据大小
	 * @param response_data		输出参数，响应数据
	 * @param response_size		输出参数，响应数据大小
	 * @return					状态码
	 */
	virtual unsigned int process(
		std::shared_ptr<Session> session,
		std::shared_ptr<char> request_data, 
		size_t request_size,
		std::shared_ptr<char>& response_data, 
		size_t& response_size) = 0;
};


/**
 * IRequestHandler的创建工厂
 */
class RequestHandlerFactory {
public:
	std::shared_ptr<IRequestHandler> create();
};


} // namespace impl
} // namespace server
} // namespace fasci_rpc