#pragma once

#include <exception>

namespace fasci_rpc {
namespace client {

class RpcException : public std::exception {
public:
	RpcException(unsigned int status) : _status(status) { }

	const char* what() const;

private:
	unsigned int _status;
};

} // namespace client 
} // namespace fasci_rpc