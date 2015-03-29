#pragma once

#include <string>

namespace fasci_rpc {
namespace server {
namespace utility {

/**
 * ��ʼ���������ڳ���ʼʱ����
 */
void log2fileInit(const char* file_name);

/**
 * д����־���Զ�����ʱ��ͻ��з�
 */
void log2fileWrite(const std::string& log_content);


} // namespace utility
} // namespace server
} // namespace fasci_rpc