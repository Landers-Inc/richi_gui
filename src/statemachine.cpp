#include "statemachine.h"

StateMachine *StateMachine::instance = nullptr;

void StateMachine::startingPeripherals() {
    currentState = PERIPHERALS;
}

void StateMachine::peripheralsReady() {
    currentState = IDLE;
}

void StateMachine::newLog() {
    currentState = NEWLOG;
}

void StateMachine::preblastLog() {
    currentState = PREBLAST;
}

void StateMachine::postblastLog() {
    currentState = POSTBLAST;
}

void StateMachine::gotoIdle() {
    currentState = IDLE;
}