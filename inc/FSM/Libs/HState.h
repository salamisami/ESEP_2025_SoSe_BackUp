#ifndef HSTATE_H
#define HSTATE_H
#pragma once

#include "Event.h"
#include "ContextData.h"
#include "State.h"
#include <iostream>


class HState : public State {
    //============================================ constructors & destructors ============================================
public:
    /**
     * @brief HState is a hierarchial state. It contains one substate as a pointer. This HState also contains entry and exit functions.
     * @param data a global context data. The data will be forwarded to parent class (State)
     * @param initial_substate the initial of the substate inside this hierarchial state
     * @param default_exit_next_state the next state to go, after the substate has reached the default exit.
     */
    HState(ContextData* data, State* initial_substate, State* default_exit_next_state = nullptr)
        :State(data)
        , substate(initial_substate)
        , default_exit_state_(default_exit_next_state) {
        //std::cout << "HState Constructor" << std::endl;
    }

    //Disable copy constructor, because we're going to use clone() instead
    HState(const HState& other) = delete;
    virtual ~HState() override {
        //std::cout << "HState Destructor" << std::endl;
        if(substate != nullptr) {
            delete substate;
        }
    }

    //================================================ public functions ================================================
public:
    virtual void entry() override {
        //PRINT_STATE;
        substate->entry();
    }
    virtual void exit() override {
        //PRINT_STATE;
        substate->exit();
    }

    //virtual State* clone() override = 0;

    virtual std::string get_current_state() override {
        std::string substate_name = substate->get_current_state();
        return substate_name;
    }

    //================================================ internal events ================================================
    virtual State* timer(TIMER_ID id) override {
        if(substate == nullptr) {
            return nullptr;
        }
        State* newSubstate = substate->timer(id);
        if(newSubstate == State::EXIT_STATE) {
            // Handle substate exit
            substate->exit();
            delete substate;
            substate = nullptr;

            // Return default exit state to parent
            return default_exit_state_;
        } else if(newSubstate != nullptr) {
            // there is substate change, change only the substate
            substate->exit();
            delete substate;
            substate = newSubstate;
            substate->entry();
        }
        return nullptr;
    }



    //================================================ private variables ================================================
protected:
    State* substate;
    State* default_exit_state_;  // State to transition to on exit

    //================================================ protected ================================================
protected:
    State* handle_event_using_function(State* (State::* handler_function)()) override {
        if(substate == nullptr) {
            return nullptr;
        }
        State* newSubstate = (substate->*handler_function)();
        if(newSubstate == State::EXIT_STATE) {
            // Handle substate exit
            substate->exit();
            delete substate;
            substate = nullptr;

            // Return default exit state to parent
            return default_exit_state_;
        } else if(newSubstate) {
            // Normal state transition
            substate->exit();
            delete substate;
            substate = newSubstate;
            newSubstate->entry();
        }
        return nullptr;
    }

};

#endif