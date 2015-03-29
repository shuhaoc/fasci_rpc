#include "stdafx.h"

#include "../rpc_server/rpc_server.h"
#include "../rpc_server/service_object_factory.h"
#include "../rpc_server/log2file.h"

using namespace std;
using namespace fasci_rpc::server;
using namespace fasci_rpc::server::utility;

class TestService : public IServiceObject {
public:
	void hello() { }

	int version() { return 1; }

	void print(const string& content) { }

	string tos(int n) { return "123"; }

	void login(const string& username, const string& password) { }

	int plus(int a, int b) { return a + b; }

	std::shared_ptr<IServiceMethod> queryMethod(const std::string& name) {
		if (name == "version") {
			return createServiceMethod(this, &TestService::version);
		} else if (name == "hello") {
			return createServiceMethod(this, &TestService::hello);
		} else if (name == "print") {
			return createServiceMethod(this, &TestService::print);
		} else if (name == "tos") {
			return createServiceMethod(this, &TestService::tos);
		} else if (name == "plus") {
			return createServiceMethod(this, &TestService::plus);
		} else if (name == "login") {
			return createServiceMethod(this, &TestService::login);
		} else {
			return nullptr;
		}
	}
};

class ServiceObjectFactory : public IServiceObjectFactory {
public:
	~ServiceObjectFactory() { }

	std::map<std::string, std::shared_ptr<IServiceObject> > create() {
		std::map<std::string, std::shared_ptr<IServiceObject> > ret;
		ret["TestService"] = std::shared_ptr<IServiceObject>(new TestService());
		return ret;
	}
};

int main() {
	using namespace std;
	using namespace fasci_rpc::server;

	log2fileInit("log.txt");
	log2fileWrite("server initializes");
	try {
		boost::asio::io_service io_service;
		RpcServer svr(io_service);
		svr.registerServiceFactory(shared_ptr<IServiceObjectFactory>(new ServiceObjectFactory()));
		svr.init("127.0.0.1", 5216, 2);
		io_service.run();
	} catch (exception& ex) {
		log2fileWrite(ex.what());
		cout << ex.what() << endl;
	}
}