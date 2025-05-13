/*
 * action.h
 *
 *  Created on: 05.05.2025
 *      Author: User
 */

#ifndef ACTION_H_
#define ACTION_H_

#include "Data.h"

class Action {
private:
	Data *data;
public:
	Action(Data *data);
	virtual ~Action() = default;

	int send_event();
	int build_connection(char* attach_point);
	bool all_connected();
	int dispatcher_online();
};

#endif /* ACTION_H_ */
