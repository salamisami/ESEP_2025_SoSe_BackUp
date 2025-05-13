/*
 * data.cpp
 *
 *  Created on: 05.05.2025
 *      Author: Thomas
 */

#include "Data.h"

Data::Data() {
	fsm_connection = false;
	hal_connection = false;
	qnet_connection = false;
	mqtt_connection = false;
	event = 0;
	rcid_fsm = 0;
	rcid_hal = 0;
	rcid_mqtt = 0;
	rcid_qnet = 0;
}

void Data::set_fsm_connection(bool connection_status){
	 fsm_connection = connection_status;
}

bool Data::fsm_connected(){
	return fsm_connection;
}

void Data::set_hal_connection(bool connection_status){
	hal_connection = connection_status;
}

bool Data::hal_connected(){
	return hal_connection;
}

void Data::set_qnet_connection(bool connection_status){
	qnet_connection = connection_status;
}

bool Data::qnet_connected(){
	return qnet_connection;
}

void Data::set_mqtt_connection(bool connection_status){
	mqtt_connection = connection_status;
}

bool Data::mqtt_connected(){
	return mqtt_connection;
}

void Data::save_event(int event){
	this->event = event;
}

int Data::get_event(){
	return event;
}

void Data::set_rcid_fsm(int rcid){
	rcid_fsm = rcid;
}

void Data::set_rcid_hal(int rcid){
	rcid_hal = rcid;
}

void Data::set_rcid_mqtt(int rcid){
	rcid_mqtt = rcid;
}

void Data::set_rcid_qnet(int rcid){
	rcid_qnet = rcid;
}

int Data::get_rcid_fsm(){
	return rcid_fsm;
}

int Data::get_rcid_hal(){
	return rcid_hal;
}

int Data::get_rcid_mqtt(){
	return rcid_mqtt;
}

int Data::get_rcid_qnet(){
	return rcid_qnet;
}
