#pragma once

namespace fasci_rpc {
namespace common {


enum StatusCode {
	SUCCESS,				// 调用成功
	PACKET_SIZE_TOO_LARGE,	// 请求包大小超常
	BAD_REQUEST,			// 请求包反序列化失败
	SERVICE_NOT_FOUND,		// 服务名不存在
	METHOD_NOT_FOUND,		// 方法名不存在
	SERVER_CALL_FAILED		// 服务端调用方法出错
};


} // namespace common
} // namespace fasci_rpc