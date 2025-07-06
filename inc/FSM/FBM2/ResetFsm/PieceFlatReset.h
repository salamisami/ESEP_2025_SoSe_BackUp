/*
 * PieceFlatReset.h
 *
 *  Created on: 04.07.2025
 *      Author: User
 */

#ifndef SRC_FSM_FBM2_RESETFSM_PIECEFLATRESET_H_
#define SRC_FSM_FBM2_RESETFSM_PIECEFLATRESET_H_
#include "ContextData.h"
#include "State.h"
#include "IdleReset.h"

class PieceFlatReset : public State{
public:
	PieceFlatReset(ContextData* data) : State(data){};
	virtual ~PieceFlatReset(){};

	void entry() override;
	void exit() override;

	State* error_w_lost() override;
	State* sorted() override;
};

#endif /* SRC_FSM_FBM2_RESETFSM_PIECEFLATRESET_H_ */
