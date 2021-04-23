import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import QmlEnumDef 1.0
import EnumDef 1.0
import QmlDevPanelModel 1.0
import QmlMeasureModel 1.0
import FontManager 1.0
import "../control/"
import "./image/"
import "./dialog/"
Item {
    id: scene

    property var baseWindow : null

    height: 1020; width : 600

    signal signalEventFinishedMeasure(int loadRPM, int nonLoadRPM, bool isSucc)

    QmlDevPanelModel{
        id : model

        onSignalEventFinishedMeasure: {
            scene.signalEventFinishedMeasure(loadRPM, nonLoadRPM, isSucc)
        }
    }

    Rectangle{
        anchors.fill: parent
        color: "#00000000"//"#590085FF"
        clip: true
        visible : model.mAutoStep !== QmlEnumDef.AUTOSTEP_NONE

        Image{
            id : autoRunBusy
            height: Math.sqrt((parent.height * parent.height) + (parent.width * parent.width)); width: parent.width * 0.5
            anchors.verticalCenter: parent.verticalCenter; anchors.horizontalCenter: parent.horizontalCenter
            source: "image/gradient.png";

            PropertyAnimation{
                target: autoRunBusy
                loops: Animation.Infinite
                property: "rotation"
                from: 0
                to : 360
                running: model.mAutoStep !== QmlEnumDef.AUTOSTEP_NONE
                duration: 6000
            }
        }
    }

    BorderImage {
        id: bg
        height: parent.height + 200; width: parent.width + 200
        anchors.verticalCenter: parent.verticalCenter; anchors.horizontalCenter: parent.horizontalCenter
        border.left: 142; border.top: 142
        border.right: 142; border.bottom: 142

        source: "image/n-phone-panel-bg.png"
    }

    ColumnLayout{
        anchors.top: parent.top; anchors.topMargin: 20; anchors.bottom: parent.bottom; anchors.bottomMargin: 30; anchors.left: parent.left; anchors.leftMargin: 30; anchors.right: parent.right; anchors.rightMargin: 30
        spacing: 30

        Item{
            Layout.preferredHeight: 80
            Layout.fillHeight: true
            Layout.fillWidth: true

            UiText{
                id : currRPMLabel
                width: 100
                anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.left;

                verticalAlignment: Text.AlignVCenter;
                text: "실시간"
            }

            Rectangle{
                height: parent.height
                anchors.left: currRPMLabel.right; anchors.leftMargin: 10; anchors.right: commIndi.left; anchors.rightMargin: 30
                color: "#59000000"
                radius: 10

                UiText{
                    width: parent.width - 60
                    anchors.verticalCenter: parent.verticalCenter; anchors.horizontalCenter: parent.horizontalCenter

                    color: "#3F464E"
                    verticalAlignment: Text.AlignVCenter; horizontalAlignment: Text.AlignRight
                    text: model.mCurrRPM.toLocaleString(FontManager.locale, 'f', 0)
                    font.pixelSize: 40
                }

                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        var dlg = graphDlg.createObject(scene,{"devModel":model})
                        dlg.open()
                    }
                }
            }

            Image{
                id : commIndi
                height: 40; width: 40
                anchors.top: parent.top; anchors.right: alarmIndi.left; anchors.rightMargin: 20
                source: model.mIsConnect ? "image/icon-ok-net.png" : "image/icon-err-net.png"
            }

            Image{
                id : alarmIndi
                height: 40; width: 40
                anchors.top: parent.top; anchors.right: parent.right;
                source: model.mIsAlarm ? "image/icon-err-check.png" : "image/icon-check.png"
            }
        }

        UiPanel {
            Layout.preferredHeight: 160
            Layout.fillHeight: true
            Layout.fillWidth: true

            source: "image/n-panel-bg.png"

            Rectangle{
                anchors.fill: parent
                color : "#390085FF"
                radius: 20

                visible: model.mAutoStep === QmlEnumDef.AUTOSTEP_CHUCK
            }

            UiText{
                id : chuckLabel
                anchors.top : parent.top; anchors.topMargin: 20; anchors.left: parent.left; anchors.leftMargin: 20
                text: qsTr("AIR 공급(전진-후진)")
            }

            UiText{
                anchors.top : chuckLabel.bottom; anchors.bottom: parent.bottom; anchors.left: parent.left; anchors.right: chuckBtn.left
                verticalAlignment: Text.AlignVCenter; horizontalAlignment: Text.AlignHCenter
                text: model.mIsChuckConnect ? "전진" : "후진"
                color : "#3F464E"
                font.pixelSize: 40
            }

            UiButton{
                id : chuckBtn
                height: 100; width: 100
                anchors.verticalCenter: parent.verticalCenter; anchors.right: parent.right; anchors.rightMargin: 30

                norImage: "image/n-circle-btn-bg.png"
                pressImage: "image/n-circle-btn-press-bg.png"

                enabled: model.mAutoStep === QmlEnumDef.AUTOSTEP_NONE

                onClicked: {
                    var strRet;
                    if(model.mIsChuckConnect)
                        strRet = model.onCommandDisconnectChuck()
                    else
                        strRet = model.onCommandConnectChuck()

                    if(strRet !== "")
                    {
                        baseWindow.showToast(strRet)
                    }
                }
            }

            Image{
                anchors.fill: chuckBtn
                source: model.mIsChuckConnect ? "image/icon-valve-connect.png" : "image/icon-valve-disconnect.png"
            }
        }

        UiPanel {
            Layout.preferredHeight: 160
            Layout.fillHeight: true
            Layout.fillWidth: true

            source: "image/n-panel-bg.png"

            Rectangle{
                anchors.fill: parent
                color : "#390085FF"
                radius: 20

                visible: model.mAutoStep === QmlEnumDef.AUTOSTEP_AIR
            }

            UiText{
                id :airLabel
                anchors.top : parent.top; anchors.topMargin: 20; anchors.left: parent.left; anchors.leftMargin: 20
                text: qsTr("AIR 공급(ON-OFF)")
            }

            UiText{
                anchors.top : airLabel.bottom; anchors.bottom: parent.bottom; anchors.left: parent.left; anchors.right: airBtn.left
                verticalAlignment: Text.AlignVCenter; horizontalAlignment: Text.AlignHCenter
                text: model.mIsValveOpen ? "ON" : "OFF"
                color : "#3F464E"
                font.pixelSize: 40
            }

            UiButton{
                id : airBtn
                height: 100; width: 100
                anchors.verticalCenter: parent.verticalCenter; anchors.right: parent.right; anchors.rightMargin: 30

                norImage: "image/n-circle-btn-bg.png"
                pressImage: "image/n-circle-btn-press-bg.png"

                enabled: model.mAutoStep === QmlEnumDef.AUTOSTEP_NONE

                onClicked: {
                    var strRet;

                    if(model.mIsValveOpen)
                        strRet = model.onCommandCloseValve()
                    else
                        strRet = model.onCommandOpenValve()

                    if(strRet !== "")
                    {
                        baseWindow.showToast(strRet)
                    }
                }
            }

            Image{
                anchors.fill: airBtn
                source: model.mIsValveOpen ? "image/icon-air-on.png" : "image/icon-air-off.png"
            }
        }

        UiPanel {
            id : loadMeasureBox

            property  QmlMeasureModel loadMeasureModel: null

            Layout.preferredHeight: 160
            Layout.fillHeight: true
            Layout.fillWidth: true

            source: "image/n-panel-bg.png"

            Component.onCompleted: {
                loadMeasureModel = model.onCommandGetLoadMeasureModel()
            }

            Rectangle{
                anchors.fill: parent
                color : "#390085FF"
                radius: 20

                visible: model.mMeasureState == QmlEnumDef.MEASURE_STATE_LOAD
            }


            UiText{
                id : loadLabel
                anchors.top : parent.top; anchors.topMargin: 20; anchors.left: parent.left; anchors.leftMargin: 20
                text: "" + (loadMeasureBox.loadMeasureModel.mNM / 1000) + qsTr(" kgf·cm 부하(") + loadMeasureBox.loadMeasureModel.mConditionFrom.toLocaleString(FontManager.locale, 'f', 0) + ")"
            }

            Item{
                width: 100
                anchors.top : loadLabel.bottom; anchors.bottom: parent.bottom; anchors.left: parent.left; anchors.leftMargin: 20

                Item{
                    id: loadSuccLamp
                    height: parent.height * 0.5; width: 24
                    anchors.top : parent.top; anchors.left: parent.left;
                    Image {
                        width: 70; height: 70
                        anchors.verticalCenter: parent.verticalCenter; anchors.horizontalCenter: parent.horizontalCenter
                        source: loadMeasureBox.loadMeasureModel.mJudg === QmlEnumDef.JUDG_STATE_SUCC ? "image/lamp-green.png" : "image/lamp-off.png"
                    }
                }
                Item{
                    id: loadFailLamp
                    height: parent.height * 0.5; width: 24
                    anchors.top : parent.top; anchors.left: loadSuccLamp.right; anchors.leftMargin: 20
                    Image {
                        width: 70; height: 70
                        anchors.verticalCenter: parent.verticalCenter; anchors.horizontalCenter: parent.horizontalCenter
                        source: loadMeasureBox.loadMeasureModel.mJudg === QmlEnumDef.JUDG_STATE_FAIL ? "image/lamp-red.png" : "image/lamp-off.png"
                    }
                }

                UiText {
                    anchors.bottom: parent.bottom; anchors.bottomMargin: 20; anchors.left: parent.left;
                    text: "[" + ("00" + loadMeasureBox.loadMeasureModel.mProgressMin).slice(-2) + ":" + ("00" + loadMeasureBox.loadMeasureModel.mProgressSec).slice(-2) + "]"
                    color :  model.mMeasureState == QmlEnumDef.MEASURE_STATE_LOAD ? "#3F464E" : "#9EAEC2"
                    font.pixelSize: 20
                }
            }

            UiText{
                anchors.top : loadLabel.bottom; anchors.bottom: parent.bottom; anchors.left: parent.left; anchors.leftMargin: 30; anchors.right: loadPostFix.left; anchors.rightMargin: 10
                verticalAlignment: Text.AlignVCenter; horizontalAlignment: Text.AlignRight
                text: loadMeasureBox.loadMeasureModel.mRPM
                color :  model.mMeasureState == QmlEnumDef.MEASURE_STATE_LOAD ? "#3F464E" : "#9EAEC2"
                font.pixelSize: 40
            }

            UiText{
                id : loadPostFix
                anchors.top : loadLabel.bottom; anchors.bottom: parent.bottom; anchors.right: loadBtn.left; anchors.rightMargin: 30
                verticalAlignment: Text.AlignVCenter; horizontalAlignment: Text.AlignRight
                text: "RPM"
                color : "#9EAEC2"
                font.pixelSize: 40
            }

            UiButton{
                id : loadBtn
                height: 100; width: 100
                anchors.verticalCenter: parent.verticalCenter; anchors.right: parent.right; anchors.rightMargin: 30

                norImage: "image/n-circle-btn-bg.png"
                pressImage: "image/n-circle-btn-press-bg.png"

                enabled: model.mAutoStep === QmlEnumDef.AUTOSTEP_NONE

                onClicked: {
                    if(model.mMeasureState == QmlEnumDef.MEASURE_STATE_LOAD)
                        model.onCommandStopLoadInsp()
                    else
                        model.onCommandStartLoadInsp()
                }
            }

            Image{
                anchors.fill: loadBtn
                source: model.mMeasureState == QmlEnumDef.MEASURE_STATE_LOAD ? "image/icon-proc-ing.png" : "image/icon-proc.png"
            }
        }

        UiPanel {
            id : nonLoadMeasureBox

            property  QmlMeasureModel nonLoadMeasureModel: null

            Layout.preferredHeight: 160
            Layout.fillHeight: true
            Layout.fillWidth: true

            source: "image/n-panel-bg.png"

            Component.onCompleted: {
                nonLoadMeasureModel = model.onCommandGetNonLoadMeasureModel()
            }

            Rectangle{
                anchors.fill: parent
                color : "#390085FF"
                radius: 20

                visible: model.mMeasureState == QmlEnumDef.MEASURE_STATE_NONLOAD
            }

            UiText{
                id : nonLoadLabel
                anchors.top : parent.top; anchors.topMargin: 20; anchors.left: parent.left; anchors.leftMargin: 20
                text: qsTr("무부하(") + nonLoadMeasureBox.nonLoadMeasureModel.mConditionFrom.toLocaleString(FontManager.locale, 'f', 0) + "~" + nonLoadMeasureBox.nonLoadMeasureModel.mConditionTo.toLocaleString(FontManager.locale, 'f', 0) + ")"
            }

            Item{
                width: 100
                anchors.top : nonLoadLabel.bottom; anchors.bottom: parent.bottom; anchors.left: parent.left; anchors.leftMargin: 20

                Item{
                    id: nonLoadSuccLamp
                    height: parent.height * 0.5; width: 24
                    anchors.top : parent.top; anchors.left: parent.left;
                    Image {
                        width: 70; height: 70
                        anchors.verticalCenter: parent.verticalCenter; anchors.horizontalCenter: parent.horizontalCenter
                        source: nonLoadMeasureBox.nonLoadMeasureModel.mJudg === QmlEnumDef.JUDG_STATE_SUCC ? "image/lamp-green.png" : "image/lamp-off.png"
                    }
                }
                Item{
                    id: nonLoadFailLamp
                    height: parent.height * 0.5; width: 24
                    anchors.top : parent.top; anchors.left: nonLoadSuccLamp.right; anchors.leftMargin: 20
                    Image {
                        width: 70; height: 70
                        anchors.verticalCenter: parent.verticalCenter; anchors.horizontalCenter: parent.horizontalCenter
                        source: nonLoadMeasureBox.nonLoadMeasureModel.mJudg === QmlEnumDef.JUDG_STATE_FAIL ? "image/lamp-red.png" : "image/lamp-off.png"
                    }
                }

                UiText {
                    anchors.bottom: parent.bottom; anchors.bottomMargin: 20; anchors.left: parent.left;
                    text: "[" + ("00" + nonLoadMeasureBox.nonLoadMeasureModel.mProgressMin).slice(-2) + ":" + ("00" + nonLoadMeasureBox.nonLoadMeasureModel.mProgressSec).slice(-2) + "]"
                    color :  model.mMeasureState == QmlEnumDef.MEASURE_STATE_NONLOAD ? "#3F464E" : "#9EAEC2"
                    font.pixelSize: 20
                }
            }

            UiText{
                anchors.top : nonLoadLabel.bottom; anchors.bottom: parent.bottom; anchors.left: parent.left; anchors.leftMargin: 30; anchors.right: nonLoadPostFix.left; anchors.rightMargin: 10
                verticalAlignment: Text.AlignVCenter; horizontalAlignment: Text.AlignRight
                text: nonLoadMeasureBox.nonLoadMeasureModel.mRPM
                color :  model.mMeasureState == QmlEnumDef.MEASURE_STATE_NONLOAD ? "#3F464E" : "#9EAEC2"
                font.pixelSize: 40
            }

            UiText{
                id : nonLoadPostFix
                anchors.top : nonLoadLabel.bottom; anchors.bottom: parent.bottom; anchors.right: nonLoadBtn.left; anchors.rightMargin: 30
                verticalAlignment: Text.AlignVCenter; horizontalAlignment: Text.AlignRight
                text: "RPM"
                color : "#9EAEC2"
                font.pixelSize: 40
            }


            UiButton{
                id : nonLoadBtn
                height: 100; width: 100
                anchors.verticalCenter: parent.verticalCenter; anchors.right: parent.right; anchors.rightMargin: 30

                norImage: "image/n-circle-btn-bg.png"
                pressImage: "image/n-circle-btn-press-bg.png"

                enabled: model.mAutoStep === QmlEnumDef.AUTOSTEP_NONE

                onClicked: {
                    if(model.mMeasureState == QmlEnumDef.MEASURE_STATE_NONLOAD)
                        model.onCommandStopNonLoadInsp()
                    else
                        model.onCommandStartNonLoadInsp()
                }
            }

            Image{
                anchors.fill: nonLoadBtn
                source: model.mMeasureState == QmlEnumDef.MEASURE_STATE_NONLOAD ? "image/icon-proc-ing.png" : "image/icon-proc.png"
            }
        }

        UiPanel {
            id : autoMeasureTime

            property  QmlMeasureModel nonLoadMeasureModel: null

            Layout.preferredHeight: 80
            Layout.fillHeight: true
            Layout.fillWidth: true

            source: "image/n-panel-bg.png"

            UiText{
                id : autoMeasureTimeLable
                anchors.top : parent.top; anchors.topMargin: 20; anchors.left: parent.left; anchors.leftMargin: 20
                text: qsTr("자동검사 시간")
            }

            UiText{
                anchors.verticalCenter: parent.verticalCenter; anchors.right: parent.right; anchors.rightMargin:30
                verticalAlignment: Text.AlignVCenter; horizontalAlignment: Text.AlignRight
                color :  model.mAutoStep !== QmlEnumDef.AUTOSTEP_NONE ? "#3F464E" : "#9EAEC2"
                font.pixelSize: 40

                text:("00" + model.mAutoMeasureMin).slice(-2) + ":" + ("00" + model.mAutoMeasureSec).slice(-2)
            }
        }

        Item{
            Layout.preferredHeight: 100
            Layout.fillHeight: true
            Layout.fillWidth: true

            RowLayout{
                spacing: 30
                anchors.fill: parent

                UiButton{
                    textColor: "#FFFFFF"
                    text: qsTr("자동")
                    Layout.preferredWidth: 1
                    Layout.fillHeight: true
                    Layout.fillWidth: true

                    norImage: "image/n-green-btn-bg.png"
                    pressImage: "image/n-green-btn-press-bg.png"

                    isOn: model.mAutoStep !== QmlEnumDef.AUTOSTEP_NONE

                    onClicked: {
                        model.onCommandStartAutoInsp()
                    }
                }

                UiButton{
                    textColor: "#FFFFFF"
                    text: qsTr("정지")
                    Layout.preferredWidth: 1
                    Layout.fillHeight: true
                    Layout.fillWidth: true

                    norImage: "image/n-red-btn-bg.png"
                    pressImage: "image/n-red-btn-press-bg.png"

                    onClicked: {
                        model.onCommandStopInsp()
                    }
                }
            }
        }
    }

    Component{
        id : graphDlg

        GraphDlg{
        }
    }
}





/*##^##
Designer {
    D{i:0;formeditorZoom:0.8999999761581421}
}
##^##*/
