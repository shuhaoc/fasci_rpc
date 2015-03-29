#pragma once

#include "service_method.h"

namespace fasci_rpc {
namespace server {


/**
 * 服务对象，每个会话会创建相应的对象
 */
class IServiceObject {
public:
	virtual ~IServiceObject() { }

	/**
	 * 通过方法名查询方法对象
	 */
	virtual std::shared_ptr<IServiceMethod> queryMethod(const std::string& name) = 0;
};


} // namespace server
} // namespace fasci_rpc 