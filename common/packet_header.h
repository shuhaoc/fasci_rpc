#pragma once

namespace fasci_rpc {
namespace common {


/**
 * 请求数据包头
 */
struct RequestHeader {
	size_t size;		// 数据包大小，不含字节数

	RequestHeader() : size(0) { }
};

/**
 * 响应数据包头
 */
struct ResponseHeader {
	size_t status;		// 状态码
	size_t size;		// 数据包大小，不含头部，仅当status为SUCCESS时有效，其他情况为0

	ResponseHeader() : status(0), size(0) { }
};

/* 请求数据包大小限制，不含头部 */
#define REQUEST_PACKET_SIZE_LIMIT (1U << 10)


} // namespace common
} // namespace fasci_rpc