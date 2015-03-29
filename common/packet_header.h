#pragma once

namespace fasci_rpc {
namespace common {


/**
 * �������ݰ�ͷ
 */
struct RequestHeader {
	size_t size;		// ���ݰ���С�������ֽ���

	RequestHeader() : size(0) { }
};

/**
 * ��Ӧ���ݰ�ͷ
 */
struct ResponseHeader {
	size_t status;		// ״̬��
	size_t size;		// ���ݰ���С������ͷ��������statusΪSUCCESSʱ��Ч���������Ϊ0

	ResponseHeader() : status(0), size(0) { }
};

/* �������ݰ���С���ƣ�����ͷ�� */
#define REQUEST_PACKET_SIZE_LIMIT (1U << 10)


} // namespace common
} // namespace fasci_rpc