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
	data->sender->send_event((int8_t) Topic::INTERNAL,(int8_t) Internal_Enum::RESET_TO_TALL_W_METAL,(int8_t) EventPriority::DEFAULT);
	return new IdleReset(data);
}

State* PieceTallWMetall::piece_switched(){
	data->sender->send_event((int8_t) Topic::INTERNAL, (int8_t) Internal_Enum::RESET_TO_TALL_W_METAL, (int8_t) EventPriority::DEFAULT);
	return new IdleReset(data);
}

State* PieceTallWMetall::clone() {
	return new PieceTallWMetall(data);
}
