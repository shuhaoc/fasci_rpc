#include "stdafx.h"

#include "thread_pool.h"

using namespace boost::posix_time;
using namespace fasci_rpc::server::utility;

ThreadPool::ThreadPool() {
}

ThreadPool::~ThreadPool() {
}

void ThreadPool::init(size_t threads) {
	for (size_t i = 0; i < threads; i++) {
		_thread_group.create_thread([this]() {
			while (1) {
				Task t;
				_queue_mutex.lock();
				if (_task_queue.empty()) {
					_queue_mutex.unlock();
				} else {
					t = _task_queue.front();
					_task_queue.pop();
					_queue_mutex.unlock();
					t();
				}
				boost::this_thread::sleep(microseconds(1));
			}
		});
	}
}

void ThreadPool::addTask(Task task) {
	using namespace boost;
	lock_guard<mutex> _(_queue_mutex);
	_task_queue.push(task);
}

void ThreadPool::join() {
	_thread_group.join_all();
}