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
    OrthState(ContextData* data, std::deque<State*> initial_substates, State* default_exit_state = nullptr, bool direct_exit = false, bool quit_on_empty = true)
        : State(data)
        , substates(initial_substates)
        , default_exit_state_(default_exit_state)
        , direct_exit_(direct_exit)
        , quit_on_empty_(quit_on_empty) {
        //std::cout << "OrthState Constructor" << std::endl;
    }
    //Disable copy constructor, because we're going to use clone() instead
    OrthState(const OrthState&) = delete;
    virtual ~OrthState() {
        if(default_exit_state_ != nullptr) {
            delete default_exit_state_;
        }
        //std::cout << "OrthState Destructor" << std::endl;
        for(auto it = substates.begin(); it != substates.end(); ) {
            State*& current_substate = *it;  // Use reference to pointer
            delete current_substate;
            ++it;
        }
    }

    //================================================ public functions ================================================
public:
    virtual void entry() override {
        //PRINT_STATE;
        for(auto it = substates.begin(); it != substates.end(); ) {
            State*& current_substate = *it;  // Use reference to pointer
            current_substate->entry();
            ++it;
        }
    }
    virtual void exit() override {
        //PRINT_STATE;
        for(auto it = substates.begin(); it != substates.end(); ) {
            State*& current_substate = *it;  // Use reference to pointer
            if(current_substate != nullptr) {
                current_substate->exit();
            }
            ++it;
        }
    }

    // virtual State* clone() override {
    //     throw std::runtime_error("Error, the clone of following state is called due to history, but not implemented: " + get_current_state());
    // }


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
        if(substates.empty()) {
            const char* state_name = typeid(*this).name();
            return demangle(state_name);
        }

        std::string appended_string;
        bool first = true; // To avoid leading space
        for(auto it = substates.begin(); it != substates.end(); ) {
            State*& current_substate = *it;  // Use reference to pointer
            if(!first) {
                appended_string += " "; // Add space between substates
            }
            appended_string += current_substate->get_current_state();
            first = false;
            ++it;
        }
        return appended_string;
    }

    virtual State* timer(TIMER_ID id) override {
        if(substates.empty() && quit_on_empty_) {
            return default_exit_state_;
        }

        auto it = substates.begin();
        while(it != substates.end()) {
            State*& current_substate = *it;
            State* newSubstate = current_substate->timer(id);

            if(newSubstate == State::EXIT_STATE) {
                // Handle exit case
                current_substate->exit();
                delete current_substate;
                it = substates.erase(it);

                if(direct_exit_) {
                    if(default_exit_state_ != nullptr) {
                        return default_exit_state_->clone();
                    }
                    return default_exit_state_;
                }

                // If we've removed all substates, return the exit state
                if(substates.empty() && quit_on_empty_) {
                    if(default_exit_state_ != nullptr) {
                        return default_exit_state_->clone();
                    }
                    return default_exit_state_;
                }
            } else if(newSubstate != nullptr && newSubstate != current_substate) {
                // Handle state transition only if it's a different state
                current_substate->exit();
                delete current_substate;
                current_substate = newSubstate;
                current_substate->entry();
                ++it;
            } else {
                // No state change
                ++it;
            }
        }

        return nullptr;
    }


    //================================================ private variables ================================================
protected:
    std::deque<State*> substates;
    State* default_exit_state_;
    bool direct_exit_;
    bool quit_on_empty_;
    std::deque<State*> clone_substates() {
        std::deque<State*> cloned_substates;
        for(auto it = substates.begin(); it != substates.end(); ) {
            State*& current_substate = *it;  // Use reference to pointer
            cloned_substates.push_back(current_substate->clone());
            ++it;
        }
        return cloned_substates;
    }

    //================================================ protected ================================================
protected:

    /**
     * If one of the states is signaling exit, just erase that substate from the entry, and go further with other states.
     * If there's no susbtates left, exit the OrthState
     */
    virtual State* handle_event_using_function(State* (State::* handler_function)()) override {
        if(substates.empty() && quit_on_empty_) {
            return default_exit_state_;
        }

        auto it = substates.begin();
        while(it != substates.end()) {
            State*& current_substate = *it;
            State* newSubstate = (current_substate->*handler_function)();

            if(newSubstate == State::EXIT_STATE) {
                // Handle exit case
                current_substate->exit();
                delete current_substate;
                it = substates.erase(it);

                if(direct_exit_) {
                    if(default_exit_state_ != nullptr) {
                        return default_exit_state_->clone();
                    }
                    return default_exit_state_;
                }

                // If we've removed all substates, return the exit state
                if(substates.empty() && quit_on_empty_) {
                    if(default_exit_state_ != nullptr) {
                        return default_exit_state_->clone();
                    }
                    return default_exit_state_;
                }
            } else if(newSubstate != nullptr && newSubstate != current_substate) {
                // Handle state transition only if it's a different state
                current_substate->exit();
                delete current_substate;
                current_substate = newSubstate;
                current_substate->entry();
                ++it;
            } else {
                // No state change
                ++it;
            }
        }

        return nullptr;
    }


};

#endif