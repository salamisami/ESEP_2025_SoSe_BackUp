#include "Worker.h"

// Worker implementation
Worker::Worker() : stop_flag(false) {
	start();
}

Worker::~Worker() {
	stop();
}

void Worker::start() {
	thread = std::thread(&Worker::run, this);
}

void Worker::stop() {
	{
		std::unique_lock<std::mutex> lock(queue_mutex);
		stop_flag = true;
	}
	condition.notify_one();

	if(thread.joinable()) {
		thread.join();
	}
}

bool Worker::isBusy() const {
	std::unique_lock<std::mutex> lock(queue_mutex);
	return !tasks.empty() || task_in_progress;
}

void Worker::run() {
	while(true) {
		std::function<void()> task;

		{
			std::unique_lock<std::mutex> lock(queue_mutex);
			condition.wait(lock, [this] {
				return stop_flag || !tasks.empty();
				});

			if(stop_flag && tasks.empty())
				return;

			task = std::move(tasks.front());
			tasks.pop();
			task_in_progress = true;
		}

		task();
		task_in_progress = false;
	}
}


