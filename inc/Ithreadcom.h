/*
 * Ithreadcom.h
 *
 *  Created on: 19.05.2025
 *      Author: Thomas
 */

#ifndef SRC_DISPATCHER_ITHREADCOM_H_
#define SRC_DISPATCHER_ITHREADCOM_H_

#include <sys/dispatch.h>

#define FBM 1

//FBM_1
#define FBM_1_HAL "Hal_1"
#define FBM_1_FSM "Fsm_1"
#define FBM_1_COM "Com_1"
#define FBM_1_RECORDER "Rec_1"
#define FBM_1_REMOTE "Rem_1"
#define FBM_1_DISPATCHER "Dis_1"
//FBM_2
#define FBM_2_HAL "Hal_2"
#define FBM_2_FSM "Fsm_2"
#define FBM_2_COM "Com_2"
#define FBM_2_RECORDER "Rec_2"
#define FBM_2_REMOTE "Rem_2"
#define FBM_2_DISPATCHER "Dis_2"

class Ithread_com {
public:
	Ithread_com(const char* name);
	virtual ~Ithread_com() = default;

	void send_event(int8_t event_code, int event_value, int priority= SIGEV_PULSE_PRIO_INHERIT);
	/*
	 * @return -1 error in MsgReceive();
	 * 	0 ein Event wird zurückgegebne
	 * 	1 eine QNX Messgae wird zurückgegeben und
	 */
	int receive_event(_pulse *event);

	name_attach_t* get_attach();

	int get_coid();

	const char* get_name();

private:
	name_attach_t *attach;
	int coid;
	const char* gns_name;
	void handle_app_msg(_pulse* msg, int rcvid);
	void handle_QNX_IO_msg(_pulse* msg, int rcvid);
	void handle_QNX_pulse(_pulse* msg, int rcvid);
};

#endif /* SRC_DISPATCHER_ITHREADCOM_H_ */
