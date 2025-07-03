#include "ServiceModeSendRamp.h"

//================================================= constructors & destructors =================================================
ServiceModeSendRamp::ServiceModeSendRamp(ContextData* data) : OrthState(data,
	std::deque<State*>({
		new IdleSMSR(data),
		new SendToRamp(data)
		})
) {
	//substate = new SubState(data);
}

ServiceModeSendRamp::~ServiceModeSendRamp() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void ServiceModeSendRamp::entry(){
	PRINT_STATE;
	data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::MOTOR_SLOW_ON);
	data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::MOTOR_RIGHT_START);
	data->sender->send_event((int8_t) Topic::ADC, (int) ADC_Enum::ADC_CALIBRATE);
	OrthState::entry();
}

void ServiceModeSendRamp::exit(){
	OrthState::exit();
    PRINT_STATE;
	data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::MOTOR_STOP);
	data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::MOTOR_SLOW_OFF);
	data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::SORTING_OFF);
}

//TODO try applying the event only to the first line of orthogonal group
State* ServiceModeSendRamp::laser_ramp_blocked(){
	for(auto& current_substate: substates){
		State* newSubstate = current_substate->laser_ramp_blocked();
		if(newSubstate != nullptr){
			return newSubstate;
		}
	}
	return nullptr;
}