import "../ui/image/."

import QtQuick 2.12
import QtQuick.Controls 2.5
import QmlEnumDef 1.0
import EnumDef 1.0
import FontManager 1.0

Item {
    id: control

    property alias boxBorder: borderLine
    property alias titleBox : titleBg
    property alias titleText: titleLabel

    Rectangle{
        id : borderLine
        width: parent.width
        anchors.top: parent.top; anchors.topMargin: titleLabel.height * 0.5; anchors.bottom: parent.bottom; anchors.horizontalCenter: parent.horizontalCenter
        border.width: 2
        border.color: "#9EAEC2"
        color :"#00000000"
    }

    Rectangle{
        id : titleBg
        height: titleLabel.height; width: titleLabel.width + 20
        anchors.verticalCenter: titleLabel.verticalCenter; anchors.horizontalCenter: titleLabel.horizontalCenter
        color : "#E7EEF7"
    }

    UiText{
        id : titleLabel
        anchors.top: parent.top; anchors.left: parent.left; anchors.leftMargin: 20

        text : "title"
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
