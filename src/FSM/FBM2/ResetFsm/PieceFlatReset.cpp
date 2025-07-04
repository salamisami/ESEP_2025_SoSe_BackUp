/*
 * PieceFlatReset.cpp
 *
 *  Created on: 04.07.2025
 *      Author: User
 */

#include "PieceFlatReset.h"

void PieceFlatReset::entry(){}

void PieceFlatReset::exit(){}

State* PieceFlatReset::sorted(){
	return new IdleReset(data);
}

State* PieceFlatReset::error_w_lost(){
	data->sender->send_event(Topic::INTERNAL, Internal_Enum::RESET_TO_TALL, EventPriority::DEFAULT);
	return new IdleReset(data);
}
