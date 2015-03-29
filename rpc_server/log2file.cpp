#include "stdafx.h"

#pragma warning(disable: 4996)

#include <Windows.h>

#include "log2file.h"

using namespace std;
using namespace boost;

mutex* log2file_mutex;
HANDLE log_file;

string strNow() {
	char date[9], time[9];
	_strdate(date);
	_strtime(time);
	return string("[") +date + " " + time + "]";
}

void fasci_rpc::server::utility::log2fileInit(const char* file_name) {
	log_file = CreateFileA(file_name, GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (log_file == INVALID_HANDLE_VALUE) {
		exit(1);
	}
	SetFilePointer(log_file, 0, 0, FILE_END);
	log2file_mutex = new mutex();
}

void fasci_rpc::server::utility::log2fileWrite(const std::string& log_content) {
	string log = strNow() + log_content + "\r\n";
	lock_guard<mutex> _(*log2file_mutex);
	DWORD written_size;
	WriteFile(log_file, log.c_str(), log.size() + 1, &written_size, nullptr);
}