#ifndef PIECEAPPEAREDFEHLERUNQUITTIERT_H
#define PIECEAPPEAREDFEHLERUNQUITTIERT_H
#pragma once

#include "State.h"

class PieceAppearedFehlerUnquittiert  : public State {
public: //============================================ constructors & destructors ============================================
    PieceAppearedFehlerUnquittiert(ContextData* data) ;
    virtual ~PieceAppearedFehlerUnquittiert();
	

public: //================================================ public functions ================================================
    void entry() override;
    void exit() override;

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