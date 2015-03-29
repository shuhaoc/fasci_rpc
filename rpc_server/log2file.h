#pragma once

#include <string>

namespace fasci_rpc {
namespace server {
namespace utility {

/**
 * 初始化，必须在程序开始时调用
 */
void log2fileInit(const char* file_name);

/**
 * 写入日志，自动加入时间和换行符
 */
void log2fileWrite(const std::string& log_content);


} // namespace utility
} // namespace server
} // namespace fasci_rpc