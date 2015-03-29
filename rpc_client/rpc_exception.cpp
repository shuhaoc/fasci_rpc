#include "../common/status_code.h"
#include "rpc_exception.h"

using namespace fasci_rpc::common;
using namespace fasci_rpc::client;

const char* RpcException::what() const {
	switch (_status) {
	case PACKET_SIZE_TOO_LARGE:
		return "���ݰ���С̫��";
	case BAD_REQUEST:
		return "�������ݰ������л�ʧ��";
	case SERVICE_NOT_FOUND:
		return "RPC������������";
	case METHOD_NOT_FOUND:
		return "RPC������������";
	case SERVER_CALL_FAILED:
		return "Զ�̷�������ʧ��";
	default:
		return "�����״̬��";
	}
}