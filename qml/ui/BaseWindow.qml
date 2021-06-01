import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Window 2.12
import QtQuick.Layouts 1.3
import QmlEnumDef 1.0
import EnumDef 1.0
import "./dialog/"
import "../control/"
//import ViewManager 1.0
//import MainModel 1.0

Window {
    readonly property int  baseWidth  : 1920
    readonly property int  baseHeight : 1080

    id: window
    visible: true
    title: "RPM INSPECTOR HMI"

    width: 1920; height: 1080
    flags : Qt.FramelessWindowHint

    function showToast(text)
    {
        toast.createObject(window, {"msg":text})
    }

    onVisibilityChanged:
    {
        //if(visibility === Window.Windowed)
        //    window.showFullScreen();
    }


    Component.onCompleted:
    {
        console.debug("create")

        window.showFullScreen();
    }

    Component.onDestruction:
    {
        console.debug("[main.qml] destroy")
    }



    Rectangle{
        anchors.fill: parent
        color : "#E7EEF7"

        Image{
            id : logoImage
            x: -116
            y: 133
            source: "image/icon-novasen.png"
            rotation: 270

            MouseArea{
                anchors.fill: parent

                onDoubleClicked: {
                    var dlg = autoMeasureCfgDlg.createObject(window)
                    dlg.open()
                }
            }
        }

        UiText{
            x: 10
            y: 50 + logoImage.width

            rotation: 270
            text: "v0.2.1"
            font.pixelSize: 20
        }
    }

    RowLayout
    {
        anchors.top: parent.top; anchors.topMargin: 30; anchors.bottom: parent.bottom; anchors.bottomMargin: 30; anchors.left: parent.left; anchors.leftMargin: 90; anchors.right: parent.right; anchors.rightMargin: 90
        spacing: 60

        ReportPanel{
            id : reportPanel
            Layout.preferredHeight: 1; Layout.preferredWidth: 1100; Layout.fillHeight: true; Layout.fillWidth: true
            baseWindow : window


        }

        DevPanel
        {
            id: devPanel

            baseWindow: window
            Layout.preferredHeight: 1; Layout.preferredWidth: 600; Layout.fillHeight: true; Layout.fillWidth: true

            onSignalEventFinishedMeasure: {
                if(isSucc)
                    reportPanel.addReport(loadRPM, nonLoadRPM, isSucc)

                var dlg = judgDlg.createObject(window, {"isSucc" : isSucc })
                dlg.open()
            }
        }
    }


    Component{
        id : toast
        UiToast{
        }
    }

    Component{
        id : autoMeasureCfgDlg

        MeasureCfgDlg{
        }
    }

    Component{
        id : judgDlg
        JudgDlg{
        }
    }


}




/*##^##
Designer {
    D{i:0;formeditorZoom:1.100000023841858}
}
##^##*/
