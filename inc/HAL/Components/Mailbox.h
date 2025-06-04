#ifndef MAILBOX_H
#define MAILBOX_H
#pragma once

#include "Macros.h"
#include <mutex>
#include <semaphore.h>
#include <stdint.h>
#include <queue>


/**
 * @brief creates a Mailbox with T datatype
 */
template <typename T>
class Mailbox {
public: //============================================ contructors & destructors ============================================
	Mailbox(uint8_t mailbox_size) : limited_size(true), capacity(mailbox_size) {
		if(sem_init(&vacant, 0, mailbox_size) == -1 ||
			sem_init(&occupied, 0, 0) == -1) {
			THROW("Failed to initialize Semaphores in Mailbox");
		}
	}
	Mailbox() : limited_size(false) {
		if(sem_init(&occupied, 0, 0) == -1) {
			THROW("Failed to initialize Semaphore in Mailbox");
		}
	}
	~Mailbox() {
		if(limited_size) {
			sem_destroy(&vacant);
		}
		sem_destroy(&occupied);
	}


public: //================================================ public functions ================================================
	/**
	 * @brief puts an element to the mailbox. Blocked if the mailbox is full
	 * @param element the item to be added to the Mailbox
	 */
	void put(T element) {
		if(limited_size) {
			sem_wait(&vacant);
		}
		mtx.lock();
		queue.push(element);
		mtx.unlock();
		sem_post(&occupied);
	}

	/**
	 * @brief takes an element from the mailbox. Blocked if the mailbox is empty
	 * @return the item from the Mailbox
	 */
	T take() {
		sem_wait(&occupied);
		mtx.lock();
		T element = queue.front();
		queue.pop();
		mtx.unlock();
		if(limited_size) {
			sem_post(&vacant);
		}
		return element;
	}


private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	std::mutex mtx;
	std::queue<T> queue;
	sem_t vacant;
	sem_t occupied;
	//pointers
	//primitive types
	uint8_t capacity;
	//bool and char
	bool limited_size;



private: //================================================ private functions ================================================
	//void privateFunction();

};

#endif