#include "../common/status_code.h"
#include "rpc_exception.h"

using namespace fasci_rpc::common;
using namespace fasci_rpc::client;

const char* RpcException::what() const {
	switch (_status) {
	case PACKET_SIZE_TOO_LARGE:
		return "数据包大小太大";
	case BAD_REQUEST:
		return "请求数据包反序列化失败";
	case SERVICE_NOT_FOUND:
		return "RPC服务名不存在";
	case METHOD_NOT_FOUND:
		return "RPC方法名不存在";
	case SERVER_CALL_FAILED:
		return "远程方法调用失败";
	default:
		return "错误的状态码";
	}
}