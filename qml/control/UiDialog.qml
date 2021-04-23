import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import QmlEnumDef 1.0
import EnumDef 1.0
import FontManager 1.0
import "./"
import "./image/"

Popup {
    id : dialog

    property alias bgSource : bgImage.source

    modal: true
    dim : true
    closePolicy: Popup.CloseOnPressOutside

    contentHeight: 900; contentWidth: 800
    anchors.centerIn : parent
    topInset: 0; bottomInset: 0; leftInset: 0; rightInset: 0; topPadding: 0; bottomPadding: 0; leftPadding: 0; rightPadding: 0

    onVisibleChanged:
    {
        if(dialog.visible)
            return;

        dialog.destroy();
    }

    background: Item{
        BorderImage {
            id : bgImage
            height: dialog.contentHeight + 200; width: dialog.contentWidth + 200
            anchors.verticalCenter: parent.verticalCenter; anchors.horizontalCenter: parent.horizontalCenter
            source: "./image/panel-bg-dialog.png"
            border.left: 110; border.top: 190
            border.right: 110; border.bottom: 190
        }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;formeditorZoom:1.75;height:480;width:640}
}
##^##*/
