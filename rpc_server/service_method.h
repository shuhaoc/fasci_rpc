#pragma once

namespace fasci_rpc {
namespace server {


/**
 * ���񷽷��ĵ��ýӿ�
 */
class IServiceMethod {
public:
	virtual ~IServiceMethod() { }

	/**
	 * �����������л�ȡ��������ִ�з������ٽ�����ֵд����Ӧ����
	 */
	virtual void execute(boost::archive::binary_iarchive& request_data,	boost::archive::binary_oarchive& response_data) = 0;
};


} // namespace server
} // namespace fasci_rpc

#include "create_service_method.h"