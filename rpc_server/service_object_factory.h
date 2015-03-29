#pragma once

#include <map>

#include "service_object.h"

namespace fasci_rpc {
namespace server {


/**
 * 服务对象抽象工厂
 */
class IServiceObjectFactory {
public:
	virtual ~IServiceObjectFactory() { }

	virtual std::map<std::string, std::shared_ptr<IServiceObject> > create() = 0;
};


} // namespace server
} // namespace fasci_rpc 