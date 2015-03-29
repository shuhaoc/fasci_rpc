#pragma once

#include <string>
#include <functional>

namespace fasci_rpc {
namespace client {


/**
 * 服务的本地代理
 */
class ServiceProxy {
private:
	ServiceProxy(const std::string& service_name, std::shared_ptr<boost::asio::ip::tcp::socket> socket);

public:
	~ServiceProxy();

public:
	template <typename Ret>
	void call(const std::string& method_name, Ret* ret);

	void call(const std::string& method_name);
	
	template <typename Arg1, typename Ret>
	void call(const std::string& method_name, Arg1 arg1, Ret* ret);
	
	template <typename Arg1>
	void call(const std::string& method_name, Arg1 arg1);
	
	template <typename Arg1, typename Arg2, typename Ret>
	void call(const std::string& method_name, Arg1 arg1, Arg2 arg2, Ret* ret);
	
	template <typename Arg1, typename Arg2>
	void call(const std::string& method_name, Arg1 arg1, Arg2 arg2);

private:
	std::shared_ptr<boost::asio::ip::tcp::socket> _socket;
	std::string _service_name;

	void callWrapper(const std::string& method_name, 
		std::function<void (boost::archive::binary_oarchive&)> send_arguments,
		std::function<void (boost::archive::binary_iarchive&)> receive_return);

	friend class RpcClient;
};

// ---------------------------------- call impletements -----------------------------------------

template <typename Ret>
void ServiceProxy::call(const std::string& method_name, Ret* ret) {
	callWrapper(method_name, 
		[](boost::archive::binary_oarchive&) { },
		[=](boost::archive::binary_iarchive& response) { response >> *ret; });
}

template <typename Arg1, typename Ret>
void ServiceProxy::call(const std::string& method_name, Arg1 arg1, Ret* ret) {
	callWrapper(method_name, 
		[=](boost::archive::binary_oarchive& request) { request << arg1; },
		[=](boost::archive::binary_iarchive& response) { response >> *ret; });
}

template <typename Arg1>
void ServiceProxy::call(const std::string& method_name, Arg1 arg1) {
	callWrapper(method_name, 
		[=](boost::archive::binary_oarchive& request) { request << arg1; },
		[](boost::archive::binary_iarchive&) { });
}

template <typename Arg1, typename Arg2, typename Ret>
void ServiceProxy::call(const std::string& method_name, Arg1 arg1, Arg2 arg2, Ret* ret) {
	callWrapper(method_name, 
		[=](boost::archive::binary_oarchive& request) { request << arg1 << arg2; },
		[=](boost::archive::binary_iarchive& response) { response >> *ret; });
}

template <typename Arg1, typename Arg2>
void ServiceProxy::call(const std::string& method_name, Arg1 arg1, Arg2 arg2) {
	callWrapper(method_name, 
		[=](boost::archive::binary_oarchive& request) { request << arg1 << arg2; },
		[](boost::archive::binary_iarchive&) { });
}


} // namespace client 
} // namespace fasci_rpc