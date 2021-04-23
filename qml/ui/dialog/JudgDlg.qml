import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import QmlEnumDef 1.0
import EnumDef 1.0
import FontManager 1.0
import "./"
import "../image/"
import "../../control/"

Popup {
    id : dialog

    property bool isSucc : false

    modal: true
    dim : true
    closePolicy: Popup.CloseOnPressOutside

    contentHeight: 700; contentWidth: 800
    anchors.centerIn: Overlay.overlay
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
            source: "/ui/image/confirm-box-bg.png"
            border.left: 110; border.top: 110
            border.right: 110; border.bottom: 110
        }
    }

    contentItem: Item {
        Rectangle{
            anchors.top: parent.top; anchors.topMargin: 30; anchors.bottom: confirmBtn.top; anchors.bottomMargin: 30; anchors.left: parent.left; anchors.leftMargin: 30; anchors.right: parent.right; anchors.rightMargin: 30
            color: dialog.isSucc ? "#00DE00" : "#FF0000"
            radius: 20

            UiText{
                id : message
                anchors.top: parent.top; anchors.topMargin: 0; anchors.bottom: parent.bottom; anchors.bottomMargin: 0; anchors.left: parent.left; anchors.leftMargin: 0; anchors.right: parent.right; anchors.rightMargin: 0
                verticalAlignment: Text.AlignVCenter; horizontalAlignment: Text.AlignHCenter
                font.pixelSize: 200

                color: dialog.isSucc ? "#FFFFFF" : "#F7FF00"

                text: dialog.isSucc ? "합격" : "불합격"
            }
        }

        UiButton{
            id : confirmBtn
            height: 100; width: 240
            anchors.bottom: parent.bottom; anchors.bottomMargin: 30; anchors.right: parent.right; anchors.rightMargin: 30
            textColor: "#9EAEC2"
            text: qsTr("확인")

            norImage: "/ui/image/n-btn-bg.png"
            pressImage: "/ui/image/n-btn-press-bg.png"

            onClicked: {
                dialog.close()
            }
        }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;formeditorZoom:1.75;height:480;width:640}
}
##^##*/
