#include "Semaphore.h"

//================================================= constructors & destructors =================================================
Semaphore::Semaphore(unsigned int count) : count_(count) {
	//substate = new SubState(data);
}



//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void Semaphore::notify() {
	std::unique_lock<std::mutex> lock(mutex_);
	++count_;
	cv_.notify_one();
}

void Semaphore::wait() {
	std::unique_lock<std::mutex> lock(mutex_);
	cv_.wait(lock, [this]() { return count_ > 0; });
	--count_;
}

bool Semaphore::try_wait() {
	std::unique_lock<std::mutex> lock(mutex_);
	if(count_ > 0) {
		--count_;
		return true;
	}
	return false;
}

unsigned int Semaphore::get_count() {
	std::unique_lock<std::mutex> lock(mutex_);
	return count_;
}