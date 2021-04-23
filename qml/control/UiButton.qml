import "../ui/image/."

import QtQuick 2.12
import QtQuick.Controls 2.5
import QmlEnumDef 1.0
import EnumDef 1.0
import FontManager 1.0

Button {
    property var textColor : "#9EAEC2"
    property var textSize  : 30
    property var isOn      : false
    property alias norImage  : bg.source
    property alias pressImage: pressBg.source

    id : control

    height: 100; width: 100
    font.family: FontManager.nanumGothicBName; font.bold  : true; font.pixelSize: textSize
    opacity: enabled ? 1.0 : 0.3

    states: State {
        name: "press"; when: control.down || control.isOn
        PropertyChanges { target: pressBg; opacity: 1}
    }

    transitions: Transition {
        to : "press"
        reversible: true
        PropertyAnimation { property: "opacity"; duration: 250 }
    }

    contentItem: Item{
        Text {
            anchors.fill: parent

            text: control.text
            font: control.font
            color: control.textColor
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            elide: Text.ElideRight
        }
    }

    background: Item{

        anchors.fill: parent

        BorderImage {
            id: bg
            height: parent.height + 200; width: parent.width + 200
            anchors.verticalCenter: parent.verticalCenter; anchors.horizontalCenter: parent.horizontalCenter
            border.left: 122; border.top: 122
            border.right: 122; border.bottom: 122

            source: control.norImage
        }

        BorderImage {
            id: pressBg
            height: parent.height + 200; width: parent.width + 200
            anchors.verticalCenter: parent.verticalCenter; anchors.horizontalCenter: parent.horizontalCenter
            border.left: 122; border.top: 122
            border.right: 122; border.bottom: 122

            source: control.pressImage
            opacity: 0
        }
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:3}
}
##^##*/
