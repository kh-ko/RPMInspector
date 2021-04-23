import "../ui/image/."

import QtQuick 2.12
import QtQuick.Controls 2.5
import QmlEnumDef 1.0
import EnumDef 1.0
import FontManager 1.0

Item {
    id : control

    property alias source : bg.source

    BorderImage {
        id: bg
        height: parent.height + 200; width: parent.width + 200
        anchors.verticalCenter: parent.verticalCenter; anchors.horizontalCenter: parent.horizontalCenter
        border.left: 142; border.top: 142
        border.right: 142; border.bottom: 142
    }
}
