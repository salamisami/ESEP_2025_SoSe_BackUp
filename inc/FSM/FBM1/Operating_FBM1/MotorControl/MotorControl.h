#ifndef MOTORCONTROL_H
#define MOTORCONTROL_H
#pragma once

#include "HState.h"
#include "Idle.h"

class MotorControl : public HState
{
public: //============================================ constructors & destructors ============================================
    MotorControl(ContextData *data);
    MotorControl(ContextData *data, State *initial_substate);
    virtual ~MotorControl();

public: //================================================ public functions ================================================
    void entry() override;
    void exit() override;
    State *clone() override;
    
    static void updateData(ContextData *data, MotorPieceState motorPieceState)
    {
        int id = data->event_payload;

        if (motorPieceState == MotorPieceState::DELETE_W_MOTOR)
        {
            // Remove the ID from the list if it exists
            if (data->workpieceList.contains(id))
            {
                data->workpieceList.remove(id);
            }
            else
            {
                printf("Warning: Trying to delete ID %d that doesn't exist in workpiece list\n", id);
            }
        }
        else
        {
            data->current_motor_speed = motorPieceState;
            // Add the ID if it doesn't exist, then update ALL workpieces to new state
            if (!data->workpieceList.contains(id))
            {
                data->workpieceList.add(id, motorPieceState);
            }
            data->workpieceList.updateStateAll(motorPieceState);
            for (auto &pair : *data->pieces_map)
            {
                Piece *piece = pair.second; // pair.second is the value (Piece*)

                // Switch case for motor states
                switch (motorPieceState)
                {
                case MotorPieceState::FAST:
                    piece->piece_tracker->fast();
                    break;
                case MotorPieceState::SLOW:
                    piece->piece_tracker->slow();
                    break;
                case MotorPieceState::STOPPED:
                    piece->piece_tracker->stop();
                    break;
                default:
                    // Handle unexpected states if needed
                    break;
                }
            }
        }
        data->workpieces = !data->workpieceList.isEmpty();
    }

private: //================================================ private variables ================================================
         // classes, STL containers, and structs
         // pointers
         // primitive types
         // bool and char
private: //================================================ private functions ================================================
         // void privateFunction();
};

#endif
