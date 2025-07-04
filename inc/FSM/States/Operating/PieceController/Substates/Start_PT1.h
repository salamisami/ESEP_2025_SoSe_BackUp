<<<<<<<< HEAD:inc/FSM/States/Operating/PieceController/Substates/Start_PT1.h
#ifndef START_PT1_H
#define START_PT1_H
========
#ifndef FASTTEMP_H
#define FASTTEMP_H
>>>>>>>> 70b3af6 (renamed temporary states):inc/FSM/TemporaryStates/PieceTracking/FastTemp.h
#pragma once

#include "State.h"
#include "StartADC_PT1.h"
#include "LocalDataPT1.h"

<<<<<<<< HEAD:inc/FSM/States/Operating/PieceController/Substates/Start_PT1.h
class Start_PT1 : public State {
public: //============================================ constructors & destructors ============================================
    Start_PT1(ContextData* data, LocalDataPT1 localdata) ;
    virtual ~Start_PT1();
	

public: //================================================ public functions ================================================
    void entry() override;
    void exit() override;
	State* clone() override;

	State* laser_front_unblocked() override;
    
========
class FastTemp : public State
{
public: //============================================ constructors & destructors ============================================
	FastTemp(ContextData *data);
	virtual ~FastTemp();

public: //================================================ public functions ================================================
	void entry() override;
	void exit() override;
>>>>>>>> 70b3af6 (renamed temporary states):inc/FSM/TemporaryStates/PieceTracking/FastTemp.h

	State *button_reset_pressed() override;

private: //================================================ private variables ================================================
<<<<<<<< HEAD:inc/FSM/States/Operating/PieceController/Substates/Start_PT1.h
	//classes, STL containers, and structs
	//pointers
	//primitive types
	LocalDataPT1 localdata_;
	//bool and char
   
	

========
		 // classes, STL containers, and structs
		 // pointers
		 // primitive types
		 // bool and char
>>>>>>>> 70b3af6 (renamed temporary states):inc/FSM/TemporaryStates/PieceTracking/FastTemp.h
private: //================================================ private functions ================================================
		 // void privateFunction();
};

#endif
