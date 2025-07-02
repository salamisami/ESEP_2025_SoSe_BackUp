/*
 * Fsm2.h
 *
 *  Created on: 02.07.2025
 *      Author: User
 */

#ifndef SRC_FSM2_FSM2_H_
#define SRC_FSM2_FSM2_H_

#include "../FBM2/Libs/OrthState.h"
#include "../FBM2/Top_level_Fsm/Boot.h"

class Fsm2 : public OrthState{
public:
	void entry() override;
	void exit() override;
	State* clone() override;

	Fsm2(ContexData* data);
	Fsm2(ContexData* data, std::vector<State*> initial_substates);
	virtual ~Fsm2();
};

#endif /* SRC_FSM2_FSM2_H_ */
