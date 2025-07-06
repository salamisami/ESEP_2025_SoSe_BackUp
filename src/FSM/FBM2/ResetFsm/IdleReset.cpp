/*
 * IdleReset.cpp
 *
 *  Created on: 04.07.2025
 *      Author: User
 */

#include "IdleReset.h"

void IdleReset::entry(){ }

void IdleReset::exit(){ }

State* IdleReset::transfer_start_flat(){
	return new PieceFlatReset(data);
}

State* IdleReset::transfer_start_tall(){
	return new PieceTallReset(data);
}

State* IdleReset::transfer_start_tall_w_metall(){
	return new PieceTallWMetall(data);
}
