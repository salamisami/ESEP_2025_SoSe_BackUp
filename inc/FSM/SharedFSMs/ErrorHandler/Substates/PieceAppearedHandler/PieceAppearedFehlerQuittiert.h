#ifndef PIECEAPPEAREDFEHLERQUITTIERT_H
#define PIECEAPPEAREDFEHLERQUITTIERT_H
#pragma once

#include "State.h"
#include "PieceAppearedNoError.h"

class PieceAppearedFehlerQuittiert : public State {
public: //============================================ constructors & destructors ============================================
    PieceAppearedFehlerQuittiert(ContextData* data) ;
    virtual ~PieceAppearedFehlerQuittiert();
	

public: //================================================ public functions ================================================
    void entry() override;
    void exit() override;

	State* clone() override;

	State* button_reset_released() override;
    


private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	//pointers
	//primitive types
	//bool and char
   
	

private: //================================================ private functions ================================================
	//void privateFunction();
	
};

#endif