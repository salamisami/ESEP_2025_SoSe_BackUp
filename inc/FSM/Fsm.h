/*
 * Fsm2.h
 *
 *  Created on: 02.07.2025
 *      Author: User
 */

#ifndef SRC_FSM2_FSM2_H_
#define SRC_FSM2_FSM2_H_

#include "OrthState.h"
#include "ContextData.h"
#include "Boot.h"
#include "IdleReset.h"

class Fsm : public OrthState{
public:
	void entry() override;
	void exit() override;

	Fsm(ContextData* data);
	Fsm(ContextData* data, std::deque<State*> initial_substates);
	virtual ~Fsm();
};

#endif /* SRC_FSM2_FSM2_H_ */
