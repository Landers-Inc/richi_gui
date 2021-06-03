#include "statemachine.h"

StateMachine *StateMachine::instance = nullptr;

std::map<State, QString> StateMachine::stateString = {
    {State::STARTUP, QCoreApplication::translate("MainWindow", "Status: Inicializando sistema")},
    {State::PERIPHERALS, QCoreApplication::translate("MainWindow", "Status: Inicializando periféricos")},
    {State::NEWLOG, QCoreApplication::translate("MainWindow", "Status: Nuevo registro configurado")},
    {State::IDLE, QCoreApplication::translate("MainWindow", "Status: Sistema listo")},
    {State::PREBLAST, QCoreApplication::translate("MainWindow", "Status: Registro pre-tronadura comenzado")},
    {State::POSTBLAST, QCoreApplication::translate("MainWindow", "Status: Registro post-tronadura comenzado")}};

void StateMachine::updateString() {
    StateMachine::stateString = {
        {State::STARTUP, QCoreApplication::translate("MainWindow", "Status: Inicializando sistema")},
        {State::PERIPHERALS, QCoreApplication::translate("MainWindow", "Status: Inicializando periféricos")},
        {State::NEWLOG, QCoreApplication::translate("MainWindow", "Status: Nuevo registro configurado")},
        {State::IDLE, QCoreApplication::translate("MainWindow", "Status: Sistema listo")},
        {State::PREBLAST, QCoreApplication::translate("MainWindow", "Status: Registro pre-tronadura comenzado")},
        {State::POSTBLAST, QCoreApplication::translate("MainWindow", "Status: Registro post-tronadura comenzado")}};
}

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