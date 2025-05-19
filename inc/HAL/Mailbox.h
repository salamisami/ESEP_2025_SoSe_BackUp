#ifndef MAILBOX_H
#define MAILBOX_H
#pragma once

#include "Macros.h"

#include <mutex>
#include <semaphore.h>
#include <stdint.h>


/**
 * @brief creates a Mailbox with T datatype
 */
template <typename T>
class Mailbox {
public: //============================================ contructors & destructors ============================================
	Mailbox(uint8_t mailbox_size) {
		int initVacant = sem_init(&vacant, 0, mailbox_size);
		int initOccupied = sem_init(&occupied, 0, 0);

		if(initVacant == -1 || initOccupied == -1) {
			THROW("Failed to initialize Semaphores in ThreadSafeQueue");
		}
	}
	virtual ~Mailbox() {
		mtx.lock();
		sem_destroy(&vacant);
		sem_destroy(&occupied);
		mtx.unlock();
	}


public: //================================================ public functions ================================================
	/**
	 * @brief puts an element to the mailbox. Blocked if the mailbox is full
	 * @param element the item to be added to the Mailbox
	 */
	void put(T element) {
		sem_wait(&vacant);
		mtx.lock();
		this->element = element;
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
		T element = this->element;
		mtx.unlock();
		sem_post(&vacant);
		return element;
	}


private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	std::mutex mtx;
	sem_t vacant;
	sem_t occupied;
	//pointers
	//primitive types
	T element;
	//bool and char



private: //================================================ private functions ================================================
	//void privateFunction();

};

#endif