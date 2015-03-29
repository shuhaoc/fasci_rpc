#include "stdafx.h"

#include <vector>

#include "../rpc_client/rpc_client.h"

using namespace std;
using namespace boost::asio;
using namespace boost::asio::ip;
using namespace fasci_rpc::client;

#include <ctime>



int main() {
	io_service io_svc;
	RpcClient client(io_svc);
	client.init("127.0.0.1", 5216);
	auto proxy = client.createServiceProxy("TestService");
	try {
		proxy->call("hello");
		int n;
		proxy->call("version", &n);
		cout << n << endl;
		proxy->call("print", string("hello world!"));
		string s;
		proxy->call("tos", 123, &s);
		cout << s << endl;
		proxy->call("login", string("shuhaoc"), string("123456"));
		int c;
		proxy->call("plus", 1, 2, &c);
		cout << c << endl;
	} catch (exception& ex) {
		cout << ex.what() << endl;
	}
}