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
	Mailbox(uint8_t size);
	virtual ~Mailbox();


public: //================================================ public functions ================================================
	/**
	 * @brief puts an element to the mailbox. Blocked if the mailbox is full
	 * @param element the item to be added to the Mailbox
	 */
	void put(T element);

	/**
	 * @brief takes an element from the mailbox. Blocked if the mailbox is empty
	 * @return the item from the Mailbox
	 */
	T take();


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