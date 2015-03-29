#pragma once

#include <functional>
#include <queue>
#include <boost/thread.hpp>
#include <boost/utility.hpp>

namespace fasci_rpc {
namespace server {
namespace utility {


/**
 * �̳߳�
 */
class ThreadPool : private boost::noncopyable {
public:
	ThreadPool();

	~ThreadPool();

private:
	typedef std::function<void ()> Task;
		
public:
	/**
	 * ���������߳�
	 */
	void init(size_t threads);

	/**
	 * �������
	 */
	void addTask(Task task);

	/**
	 * �ȴ����й����߳��˳���Ŀǰ�����߳������˳�����
	 */
	void join();

private:
	std::queue<Task> _task_queue;
	boost::mutex _queue_mutex;
	boost::thread_group _thread_group;
};


} // namespace utility 
} // namespace server 
} // namespace fasci_rpc