#pragma once

// This is singleton StateMachine class to coordinate function in the different classes
class StateMachine {
   public:
    static StateMachine *getInstance() {
        if (!instance) instance = new StateMachine;
        return instance;
    }

    typedef enum State {
        IDLE = 0,
        PERIPHERALS,
        READY,
        PREBLAST,
        POSTBLAST
    } State;

   private:
    // Static object to store the singleton instance
    static StateMachine *instance;
    // Current state in the state machine
    State currentState = IDLE;

    StateMachine(){

    };
};