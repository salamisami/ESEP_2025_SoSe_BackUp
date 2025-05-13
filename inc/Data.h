/*
 * data.h
 *
 *  Created on: 05.05.2025
 *      Author: User
 */

#ifndef DATA_H_
#define DATA_H_

#define MAX_CONNECTIONS 4
#define GNS_NAME "Dispatcher"

class Data {
public:
	Data();
	virtual ~Data() = default;

	void set_fsm_connection(bool connection_status);
	bool fsm_connected();
	void set_hal_connection(bool connection_status);
	bool hal_connected();
	void set_qnet_connection(bool connection_status);
	bool qnet_connected();
	void set_mqtt_connection(bool connection_status);
	bool mqtt_connected();
	void save_event(int event);
	int get_event();
	void set_rcid_fsm(int rcid);
	void set_rcid_hal(int rcid);
	void set_rcid_mqtt(int rcid);
	void set_rcid_qnet(int rcid);
	int get_rcid_fsm();
	int get_rcid_hal();
	int get_rcid_mqtt();
	int get_rcid_qnet();


private:
	bool fsm_connection;
	bool hal_connection;
	bool qnet_connection;
	bool mqtt_connection;
	int event;
	int rcid_fsm;
	int rcid_hal;
	int rcid_mqtt;
	int rcid_qnet;
};

#endif /* DATA_H_ */
