#pragma once

namespace fasci_rpc {
namespace server {


/**
 * 服务方法的调用接口
 */
class IServiceMethod {
public:
	virtual ~IServiceMethod() { }

	/**
	 * 从请求数据中获取参数，并执行方法，再将返回值写入响应数据
	 */
	virtual void execute(boost::archive::binary_iarchive& request_data,	boost::archive::binary_oarchive& response_data) = 0;
};


} // namespace server
} // namespace fasci_rpc

#include "create_service_method.h"