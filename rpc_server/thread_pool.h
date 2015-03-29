#pragma once

#include <functional>
#include <queue>
#include <boost/thread.hpp>
#include <boost/utility.hpp>

namespace fasci_rpc {
namespace server {
namespace utility {


/**
 * 线程池
 */
class ThreadPool : private boost::noncopyable {
public:
	ThreadPool();

	~ThreadPool();

private:
	typedef std::function<void ()> Task;
		
public:
	/**
	 * 启动工作线程
	 */
	void init(size_t threads);

	/**
	 * 添加任务
	 */
	void addTask(Task task);

	/**
	 * 等待所有工作线程退出，目前工作线程尚无退出出口
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