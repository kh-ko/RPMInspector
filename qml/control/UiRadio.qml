import QtQuick 2.12
import QtQuick.Controls 2.5
import QmlEnumDef 1.0
import EnumDef 1.0
import FontManager 1.0

RadioButton {
    id: control

    indicator: Rectangle {
        height: control.height; width: control.height
        x: 0
        y: 0
        radius: control.height/2
        border.width: 2
        border.color: "#0085FF"
        color: "#00000000"

        Rectangle {
            height: parent.height * 0.66; width: parent.width * 0.66
            anchors.verticalCenter: parent.verticalCenter; anchors.horizontalCenter: parent.horizontalCenter
            radius: height/2
            border.width: 0
            color: "#0085FF"
            visible: control.checked
        }
    }
}
