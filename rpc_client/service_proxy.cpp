#include "stdafx.h"

#include <vector>

#include "../common/packet_header.h"
#include "../common/status_code.h"
#include "rpc_exception.h"
#include "service_proxy.h"

using namespace std;
using namespace boost::asio;
using namespace boost::archive;
using namespace fasci_rpc::client;
using namespace fasci_rpc::common;

ServiceProxy::ServiceProxy(const string& name, shared_ptr<boost::asio::ip::tcp::socket> socket) : _service_name(name), _socket(socket) {
}

ServiceProxy::~ServiceProxy() {
}

void ServiceProxy::callWrapper(const std::string& method_name, 
	std::function<void (boost::archive::binary_oarchive&)> send_arguments,
	std::function<void (boost::archive::binary_iarchive&)> receive_return) {
		boost::asio::streambuf request_buffer;
		binary_oarchive request_archive(request_buffer, no_header);
		request_archive << _service_name << method_name;
		send_arguments(request_archive);
		
		vector<const_buffer> bv;
		RequestHeader request_header;
		request_header.size = request_buffer.size();
		bv.push_back(buffer(&request_header, sizeof(request_header)));
		bv.push_back(request_buffer.data());		
		write(*_socket, bv);

		ResponseHeader response_header;
		read(*_socket, buffer(&response_header, sizeof(response_header)));
		
		if (response_header.status != SUCCESS) {
			throw RpcException(response_header.status);
		}

		boost::asio::streambuf response_buffer;
		auto mutable_buffer = response_buffer.prepare(response_header.size);
		read(*_socket, mutable_buffer);
		response_buffer.commit(response_header.size);

		binary_iarchive response_archive(response_buffer, no_header);
		receive_return(response_archive);
}

void ServiceProxy::call(const std::string& method_name) {
	callWrapper(method_name, 
		[](boost::archive::binary_oarchive&) { },
		[](boost::archive::binary_iarchive& response) { });
}