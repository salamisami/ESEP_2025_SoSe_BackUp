/*
 * WaitingForComReset.h
 *
 *  Created on: 25.06.2025
 *      Author: Thomas
 */

#ifndef INC_FSM_STATES_ESTOP_WAITING_FOR_COM_RESET_H_
#define INC_FSM_STATES_ESTOP_WAITING_FOR_COM_RESET_H_

#include "State.h"
#include "EStopReleased.h"
#include "WaitingForLocalReset.h"
#include "EStopViaLocal.h"
#include "EStopViaNeighbor.h"
#include "IdleIM.h"

class WaitingForComReset : public State{
public: //============================================ constructors & destructors ============================================
	WaitingForComReset(ContextData* data);
    virtual ~WaitingForComReset();


public: //================================================ public functions ================================================
	void entry() override;
	void exit() override;

	State* button_estop_pressed() override;
	State* com_button_estop_pressed() override;
	State* com_button_reset_pressed() override;
	State* estop() override;



private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	//pointers
	//primitive types
	//bool and char



private: //================================================ private functions ================================================
	//void privateFunction();

};



#endif /* INC_FSM_STATES_ESTOP_WAITINGFORCOMRESET_H_ */
