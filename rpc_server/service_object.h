#pragma once

#include "service_method.h"

namespace fasci_rpc {
namespace server {


/**
 * �������ÿ���Ự�ᴴ����Ӧ�Ķ���
 */
class IServiceObject {
public:
	virtual ~IServiceObject() { }

	/**
	 * ͨ����������ѯ��������
	 */
	virtual std::shared_ptr<IServiceMethod> queryMethod(const std::string& name) = 0;
};


} // namespace server
} // namespace fasci_rpc 