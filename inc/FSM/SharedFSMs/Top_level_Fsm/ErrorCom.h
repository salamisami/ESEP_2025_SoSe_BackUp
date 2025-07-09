/*
 * ErrorCom.h
 *
 *  Created on: 02.07.2025
 *      Author: User
 */

#ifndef INC_FSM_FBM2_TOP_LEVEL_FSM_ERRORCOM_H_
#define INC_FSM_FBM2_TOP_LEVEL_FSM_ERRORCOM_H_

#include"State.h"

class ErrorCom : public State{
	public:
	ErrorCom(ContextData* data) : State(data){};
	virtual ~ErrorCom(){};

	void entry() override;
	void exit() override;

	State* clone() override;

	State* mqtt_error_resolved() override;
	State* com_error_resolved() override;
	State* error_c_lost_com() override;
	State* error_c_lost_mqtt() override;

};





#endif /* INC_FSM_FBM2_TOP_LEVEL_FSM_ERRORCOM_H_ */
