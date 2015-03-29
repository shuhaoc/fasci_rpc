#include "stdafx.h"

#include "../common/packet_header.h"
#include "../common/status_code.h"
#include "session.h"
#include "log2file.h"
#include "service_object.h"
#include "request_handler.h"

using namespace std;
using namespace boost::asio;
using namespace boost::archive;
using namespace fasci_rpc::server;
using namespace fasci_rpc::common;
using namespace fasci_rpc::server::utility;
using namespace fasci_rpc::server::impl;

class RequestHandler : public IRequestHandler {
public:
	/* override */
	unsigned int process(
		std::shared_ptr<Session> session,
		std::shared_ptr<char> request_data, 
		size_t request_size,
		std::shared_ptr<char>& response_data, 
		size_t& response_size) {
		boost::asio::streambuf input_buffer;
		binary_iarchive input_archive(input_buffer, no_header);

		auto data = input_buffer.prepare(request_size);
		buffer_copy(data, buffer(request_data.get(), request_size));
		input_buffer.commit(request_size);

		string service_name, method_name;
		try {
			input_archive >> service_name; 
			shared_ptr<IServiceObject> service(session->services[service_name]);
			if (service) {
				input_archive >> method_name;
				shared_ptr<IServiceMethod> method(service->queryMethod(method_name));
				if (method) {
					boost::asio::streambuf output_buffer;
					binary_oarchive output_archive(output_buffer, no_header);
					try {
						method->execute(input_archive, output_archive);
					} catch(exception& ex) {
						log2fileWrite(ex.what());
						return SERVER_CALL_FAILED;
					}
					response_size = output_buffer.size();
					response_data.reset(new char[response_size]);
					buffer_copy(buffer(response_data.get(), response_size), output_buffer.data());
					return SUCCESS;
				} else {
					return METHOD_NOT_FOUND;
				}
			} else {
				return SERVICE_NOT_FOUND;
			}
		} catch (archive_exception&) {
			return BAD_REQUEST;
		}
	}
};

std::shared_ptr<IRequestHandler> RequestHandlerFactory::create() {
	return shared_ptr<IRequestHandler>(new RequestHandler());
}