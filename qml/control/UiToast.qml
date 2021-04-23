import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import QmlEnumDef 1.0
import EnumDef 1.0
import FontManager 1.0
import "./"
import "./image/"

Popup {
    id : toast

    property alias msg : message.text

    modal: false
    dim : false
    closePolicy: Popup.CloseOnPressOutside

    opacity: 0
    x : (parent.width * 0.5) - (contentWidth * 0.5)
    y : -1 * contentHeight

    contentHeight: 120; contentWidth: 1000

    topInset: 0; bottomInset: 0; leftInset: 0; rightInset: 0; topPadding: 0; bottomPadding: 0; leftPadding: 0; rightPadding: 0

    Component.onCompleted: {
        console.debug("show toast")
        toast.open();
        showAni.start();
        timer.start();
    }

    Timer {
        id : timer
        interval: 4000; running: false; repeat: false
        onTriggered:
        {
            closeAni.start()
        }
    }

    ParallelAnimation {
        id :showAni

        NumberAnimation {
            target: toast
            properties: "opacity"
            duration: 250
            from : 0
            to: 1.0
            easing.type: Easing.InOutQuad
        }
        NumberAnimation {
            target: toast
            properties: "y"
            duration: 500
            from: -1 * contentHeight
            to : contentHeight
            easing.type: Easing.InOutQuad
        }
    }

    ParallelAnimation {
        id :closeAni

        NumberAnimation {
            target: toast
            properties: "opacity"
            duration: 250
            from : 1.0
            to: 0
            easing.type: Easing.InOutQuad
        }

        onStopped: {
            toast.visible = false;
        }
    }

    onVisibleChanged:
    {
        if(toast.visible)
            return;

        toast.destroy();
    }

    background: Rectangle
    {
        color : "#59000000"
        radius: 60
        border.color: "#0085ff"
        border.width: 5
    }

    contentItem: Text{
        id:message

        anchors.fill : parent

        verticalAlignment: Text.AlignVCenter
        horizontalAlignment : Text.AlignHCenter
        font.pixelSize: 50
        font.family: FontManager.nanumGothicName
        elide: Text.ElideRight

        color : "#FFFFFF"
        text: "Alarm disable label"
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.6600000262260437}
}
##^##*/
