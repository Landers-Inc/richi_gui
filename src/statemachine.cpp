#include "statemachine.h"

StateMachine *StateMachine::instance = nullptr;

std::map<State, const char *> StateMachine::stateString = {
    {State::STARTUP, "Status: Inicializando sistema"},
    {State::PERIPHERALS, "Status: Inicializando periféricos"},
    {State::NEWLOG, "Status: Nuevo registro configurado"},
    {State::IDLE, "Status: Sistema listo"},
    {State::PREBLAST, "Status: Registro pre-tronadura comenzado"},
    {State::POSTBLAST, "Status: Registro post-tronadura comenzado"}};

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