/*
 * PieceTallReset.cpp
 *
 *  Created on: 04.07.2025
 *      Author: User
 */

#include "PieceTallReset.h"

void PieceTallReset::entry(){}

void PieceTallReset::exit(){}

State* PieceTallReset::sorted(){
	return new IdleReset(data);
}

State* PieceTallReset::error_w_lost(){
	data->sender->send_event(Topic::INTERNAL, Internal_Enum::RESET_TO_TALL, EventPriority::DEFAULT);
	return new IdleReset(data);
}
