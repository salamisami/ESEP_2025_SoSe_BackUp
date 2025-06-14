#ifndef STOPCDS_H
#define STOPCDS_H
#pragma once

#include "HState.h"

class StopCDS : public HState {
public: //============================================ constructors & destructors ============================================
    StopCDS(ContextData* data) ;
    virtual ~StopCDS();
	

public: //================================================ public functions ================================================
    void entry() override;
    void exit() override;
    


private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	//pointers
	//primitive types
	//bool and char
   
	

private: //================================================ private functions ================================================
	//void privateFunction();
	
};

#endif
