#pragma once

namespace fasci_rpc {
namespace common {


enum StatusCode {
	SUCCESS,				// ���óɹ�
	PACKET_SIZE_TOO_LARGE,	// �������С����
	BAD_REQUEST,			// ����������л�ʧ��
	SERVICE_NOT_FOUND,		// ������������
	METHOD_NOT_FOUND,		// ������������
	SERVER_CALL_FAILED		// ����˵��÷�������
};


} // namespace common
} // namespace fasci_rpc