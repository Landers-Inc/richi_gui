#pragma once

#include <QObject>
#include <iostream>
#include <string>

typedef enum State {
    STARTUP = 0,
    PERIPHERALS,
    NEWLOG,
    IDLE,
    PREBLAST,
    POSTBLAST
} State;

// This is singleton StateMachine class to coordinate function in the different classes
class StateMachine : public QObject {
    Q_OBJECT
   public:
    static StateMachine *getInstance() {
        if (!instance) instance = new StateMachine;
        return instance;
    }

    static std::map<State, const char *> stateString;

    State getState() {
        return currentState;
    }
    void startingPeripherals();
    void peripheralsReady();
    void newLog();
    void preblastLog();
    void postblastLog();
    void gotoIdle();

    ~StateMachine() {
        std::cout << "Closing StateMachine instance" << std::endl;
    };

   private:
    // Static object to store the singleton instance
    static StateMachine *instance;
    // Current state in the state machine
    State currentState = STARTUP;

    StateMachine(){};
};
