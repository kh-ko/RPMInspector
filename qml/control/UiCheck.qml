import QtQuick 2.12
import QtQuick.Controls 2.5
import QmlEnumDef 1.0
import EnumDef 1.0
import FontManager 1.0
import "../ui/image/."

CheckBox {
    id: control

    opacity: enabled ? 1.0 : 0.3

    states: State {
        name: "press"; when: control.down || control.checked
        PropertyChanges { target: pressBg; opacity: 1}
    }

    transitions: Transition {
        to : "press"
        reversible: true
        PropertyAnimation { property: "opacity"; duration: 250 }
    }

    indicator: Image {
        anchors.fill: parent
        source: "image/n-check-bg.png"

        Image {
            id : pressBg
            anchors.fill: parent
            opacity : 0

            source: "image/n-check-press-bg.png"
        }

        Rectangle {
            height: parent.height * 0.3; width: parent.width * 0.3
            anchors.verticalCenter: parent.verticalCenter; anchors.horizontalCenter: parent.horizontalCenter
            radius: height / 2
            border.width: 0
            color: "#389CF9"
            visible: control.checked
        }

        Rectangle {
            height: parent.height * 0.4; width: parent.width * 0.4
            anchors.verticalCenter: parent.verticalCenter; anchors.horizontalCenter: parent.horizontalCenter
            radius: height / 2
            border.width: 4
            border.color: "#389CF9"
            color: "#00000000"
            visible: !control.checked
        }
    }
}
