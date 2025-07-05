#ifndef ORTHSTATE_H
#define ORTHSTATE_H
#pragma once

#include "Event.h"
#include "ContextData.h"
#include "State.h"

#include <deque>
#include <iostream>


class OrthState : public State {
    //============================================ constructors & destructors ============================================
public:
    /**
     * @brief OrthState is an orthogonal state. It contains more than one substates, which are running parallel. This OrthState also contains entry and exit functions.
     * @param data a global context data. The data will be forwarded to parent class (State)
     * @param initial_substate the initial substates inside this state
     * @param default_exit_next_state the next state to go, after the substate has reached the default exit.
     */
    OrthState(ContextData* data, std::deque<State*> initial_substates, State* default_exit_state = nullptr)
        : State(data)
        , substates(initial_substates)
        , default_exit_state_(default_exit_state) {
        //std::cout << "OrthState Constructor" << std::endl;
    }
    //Disable copy constructor, because we're going to use clone() instead
    OrthState(const OrthState&) = delete;
    virtual ~OrthState() {
        //std::cout << "OrthState Destructor" << std::endl;
        for(auto& current_substate : substates) {
            delete current_substate;
        }
        if(default_exit_state_ != nullptr){
            delete default_exit_state_;
        }
    }

    //================================================ public functions ================================================
public:
    virtual void entry() override {
        //PRINT_STATE;
        for(auto& current_substate : substates) {
            current_substate->entry();
        }
    }
    virtual void exit() override {
        //PRINT_STATE;
        for(auto& current_substate : substates) {
            if(current_substate != nullptr) {
                current_substate->exit();
            }
        }
    }

    //TODO make virtual
    virtual State* clone() override {
        DEBUG("Warning, function of abstract class OrthState::clone() is called.");
        return nullptr;
    }

    /**
     * @brief adds one substate to run parallel among with other existing substates. This function will also call the entry() of the new added substate.
     * @param input_state substate to add
     */
    void spawn_orthogonal_state(State* input_state) {
        substates.push_back(input_state);
        input_state->entry();
    }

    State* despawn_orthogonal_state() {
        State* state_to_despawn = substates.front();
        substates.pop_front();
        return state_to_despawn;
    }

    virtual std::string get_current_state() override {
        std::string appended_string;
        bool first = true; // To avoid leading space
        for(auto& current_substate : substates) {
            if(!first) {
                appended_string += " "; // Add space between substates
            }
            appended_string += current_substate->get_current_state();
            first = false;
        }
        return appended_string;
    }

    virtual State* timer(TIMER_ID id) override {
        for(auto& current_substate : substates) {
            State* newSubstate = current_substate->timer(id);
            if(newSubstate == State::EXIT_STATE) {
                // Handle substate exit
                current_substate->exit();
                delete current_substate;
                current_substate = nullptr;
                // Return default exit state to parent
                return default_exit_state_->clone();
            } else if(newSubstate != nullptr) {
                // there is substate change, change only the substate
                current_substate->exit();
                delete current_substate;
                current_substate = newSubstate;
                current_substate->entry();
            }
        }
        return nullptr;
    }


    //================================================ private variables ================================================
protected:
    std::deque<State*> substates;
    State* default_exit_state_;
    std::deque<State*> clone_substates() {
        std::deque<State*> cloned_substates;
        for(auto& current_substate : substates) {
            cloned_substates.push_back(current_substate->clone());
        }
        return cloned_substates;
    }

    //================================================ protected ================================================
protected:

    virtual State* handle_event_using_function(State* (State::* handler_function)()) override {
        for(auto it = substates.begin(); it != substates.end(); ) {
            State*& current_substate = *it;  // Use reference to pointer
            
            State* newSubstate = (current_substate->*handler_function)();

            if(newSubstate == State::EXIT_STATE) {
                // Handle exit case
                current_substate->exit();
                delete current_substate;
                it = substates.erase(it);
                return default_exit_state_->clone();
            }

            if(newSubstate != nullptr) {
                // Handle state transition
                current_substate->exit();
                delete current_substate;
                current_substate = newSubstate;
                current_substate->entry();
            }

            ++it;  // Common increment for both remaining cases
        }
        return nullptr;
    }


};

#endif