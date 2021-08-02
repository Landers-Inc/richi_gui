import QtQuick 2.4
import QtQuick.Window 2.4
import QtQuick.Controls 2.4
import QtQuick.VirtualKeyboard 2.4

InputPanel {
    id: inputPanel
    z: 99
    y: 375
    width: 440

    states: [
        State {
            name: "visible"
            when: inputPanel.active
            PropertyChanges {
                target: inputPanel
                y: 375 - inputPanel.height
            }
        }
    ]

    transitions: [
        Transition {
            id: inputPanelTransition
            from: ""
            to: "visible"
            reversible: true
            ParallelAnimation {
                NumberAnimation {
                    properties: "y"
                    duration: 250
                    easing.type: Easing.InOutQuad
                }
            }
        }
    ]
    Binding {
        target: InputContext
        property: "animating"
        value: inputPanelTransition.running
    }
}