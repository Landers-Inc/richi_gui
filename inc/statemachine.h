#pragma once

#include <QObject>

// This is singleton StateMachine class to coordinate function in the different classes
class StateMachine : public QObject {
    Q_OBJECT
   public:
    static StateMachine *getInstance() {
        if (!instance) instance = new StateMachine;
        return instance;
    }

    typedef enum State {
        STARTUP = 0,
        PERIPHERALS,
        NEWLOG,
        IDLE,
        PREBLAST,
        POSTBLAST
    } State;

    State getState() {
        return currentState;
    }
    void startingPeripherals();
    void peripheralsReady();
    void newLog();
    void preblastLog();
    void postblastLog();
    void gotoIdle();

   private:
    // Static object to store the singleton instance
    static StateMachine *instance;
    // Current state in the state machine
    State currentState = STARTUP;

    StateMachine(){};
};
