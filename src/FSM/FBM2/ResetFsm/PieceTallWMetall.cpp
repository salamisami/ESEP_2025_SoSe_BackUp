/*
 * PieceTallWMetall.cpp
 *
 *  Created on: 04.07.2025
 *      Author: User
 */

#include "PieceTallWMetall.h"

void PieceTallWMetall::entry(){}

void PieceTallWMetall::exit(){}

State* PieceTallWMetall::sorted(){
	return new IdleReset(data);
}

State* PieceTallWMetall::error_w_lost(){
	data->sender->send_event(Topic::INTERNAL, Internal_Enum::RESET_TO_TALL, EventPriority::DEFAULT);
	return new IdleReset(data);
}
