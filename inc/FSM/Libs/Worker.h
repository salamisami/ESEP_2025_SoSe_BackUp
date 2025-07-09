#ifndef WORKER_H
#define WORKER_H
#pragma once

#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <atomic>
#include <memory>

// class ThreadPool {
// public:
class Worker {
public:
	Worker();
	virtual ~Worker();

	void start();
	void stop();
	bool isBusy() const;


	template<class F, class... Args>
	void enqueue(F&& f, Args&&... args) {
		{
			std::unique_lock<std::mutex> lock(queue_mutex);

			if(stop_flag) {
				throw std::runtime_error("enqueue on stopped Worker");
			}

			tasks.emplace(std::bind(std::forward<F>(f), std::forward<Args>(args)...));
		}

		condition.notify_one();
	}

private:
	void run();

	std::thread thread;
	std::queue<std::function<void()>> tasks;
	mutable std::mutex queue_mutex;
	std::condition_variable condition;
	bool stop_flag;
	std::atomic<bool> task_in_progress{ false };
};

// 	explicit ThreadPool(size_t num_threads);
// 	~ThreadPool();

// 	template<class F, class... Args>
// 	void enqueue(F&& f, Args&&... args);

// 	template<class F, class... Args>
// 	void enqueue_to(size_t worker_id, F&& f, Args&&... args);

// 	size_t size() const { return workers.size(); }
// 	bool isWorkerBusy(size_t worker_id) const;

// private:
// 	std::vector<std::unique_ptr<Worker>> workers;
// 	std::atomic<size_t> next_worker{ 0 };
// };



#endif
