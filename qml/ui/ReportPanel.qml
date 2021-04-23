import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import QmlEnumDef 1.0
import EnumDef 1.0
import QmlReportModel 1.0
import FontManager 1.0
import "../control/"
import "./image/"
import "./dialog/"

Item {
    id : panel

    property var isRemoveUI : false
    property var baseWindow : null
    property alias reportModel : model

    function addReport(loadRPM, nonLoadRPM, isSucc)
    {
        var strLoadRPM = loadRPM.toLocaleString(FontManager.locale, 'f',0)
        var strNonLoadRPM = nonLoadRPM.toLocaleString(FontManager.locale, 'f',0)
        model.onCommandAddReport(strLoadRPM, strNonLoadRPM, isSucc)
    }

    QmlReportModel{
        id : model

        onSignalEventRefreshList: {
            listModel.clear()

            for(var i = 0; i < onCommandGetListSize(); i ++)
            {
                listModel.append({"idx": i})
            }

            reportList.positionViewAtEnd()
        }
    }

    UiPanel{
        id : title
        height: 310; width: parent.width
        anchors.top: parent.top; anchors.topMargin: 0; anchors.left: parent.left; anchors.leftMargin: 0
        source : "image/n-panel-bg"

        RowLayout{
            anchors.top: parent.top; anchors.topMargin: 0; anchors.bottom: listBtn.top; anchors.bottomMargin: 30; anchors.left: parent.left; anchors.leftMargin: 30; anchors.right: parent.right; anchors.rightMargin: 30
            spacing: 20

            Item{
                Layout.preferredWidth: 340
                Layout.preferredHeight: 1
                Layout.fillHeight: true
                Layout.fillWidth: true

                UiText{
                    height: 80;
                    anchors.top: parent.top; anchors.topMargin: 0; anchors.left: parent.left; anchors.leftMargin: 0; anchors.right: parent.right; anchors.rightMargin: 0

                    horizontalAlignment: Text.AlignHCenter; verticalAlignment: Text.AlignVCenter
                    text:"제품 모델"
                }

                UiText{
                    height: parent.height - 80;
                    anchors.bottom: parent.bottom; anchors.bottomMargin: 0; anchors.left: parent.left; anchors.leftMargin: 0; anchors.right: parent.right; anchors.rightMargin: 0

                    elide: Text.ElideRight
                    color : "#3F464E"
                    horizontalAlignment: Text.AlignHCenter; verticalAlignment: Text.AlignVCenter
                    text:panel.reportModel.mModel
                }
            }

            Item{
                Layout.preferredWidth: 300
                Layout.preferredHeight: 1
                Layout.fillHeight: true
                Layout.fillWidth: true

                UiText{
                    height: 80;
                    anchors.top: parent.top; anchors.topMargin: 0; anchors.left: parent.left; anchors.leftMargin: 0; anchors.right: parent.right; anchors.rightMargin: 0

                    horizontalAlignment: Text.AlignHCenter; verticalAlignment: Text.AlignVCenter
                    text:"제품 번호"
                }

                UiText{
                    height: parent.height - 80;
                    anchors.bottom: parent.bottom; anchors.bottomMargin: 0; anchors.left: parent.left; anchors.leftMargin: 0; anchors.right: parent.right; anchors.rightMargin: 0

                    elide: Text.ElideRight
                    color : "#3F464E"
                    horizontalAlignment: Text.AlignHCenter; verticalAlignment: Text.AlignVCenter
                    text:panel.reportModel.mPDNum
                }

            }

            Item{
                Layout.preferredWidth: 300
                Layout.preferredHeight: 1
                Layout.fillHeight: true
                Layout.fillWidth: true

                UiText{
                    height: 80;
                    anchors.top: parent.top; anchors.topMargin: 0; anchors.left: parent.left; anchors.leftMargin: 0; anchors.right: parent.right; anchors.rightMargin: 0

                    horizontalAlignment: Text.AlignHCenter; verticalAlignment: Text.AlignVCenter
                    text:"제품명"
                }

                UiText{
                    height: parent.height - 80;
                    anchors.bottom: parent.bottom; anchors.bottomMargin: 0; anchors.left: parent.left; anchors.leftMargin: 0; anchors.right: parent.right; anchors.rightMargin: 0

                    elide: Text.ElideRight
                    color : "#3F464E"
                    horizontalAlignment: Text.AlignHCenter; verticalAlignment: Text.AlignVCenter
                    text:panel.reportModel.mPDName
                }

            }
        }

        UiButton{
            id : listBtn
            height: 100; width: 240
            anchors.bottom: parent.bottom; anchors.bottomMargin: 30; anchors.right: settingBtn.left; anchors.rightMargin: 30
            textColor: "#9EAEC2"
            text: qsTr("제품목록")

            norImage: "image/n-btn-bg.png"
            pressImage: "image/n-btn-press-bg.png"

            onClicked: {
                var dlg = pdListDlg.createObject(panel, {"baseWindow":panel.baseWindow});
                dlg.open()
            }
        }

        UiButton{
            id : settingBtn
            height: 100; width: 240
            anchors.bottom: parent.bottom; anchors.bottomMargin: 30; anchors.right: parent.right; anchors.rightMargin: 30
            textColor: "#9EAEC2"
            text: qsTr("제품설정")

            norImage: "image/n-btn-bg.png"
            pressImage: "image/n-btn-press-bg.png"

            onClicked: {
                var dlg = pdSettingDlg.createObject(panel,{"oldPDNum":panel.reportModel.mPDNum, "baseWindow" : panel.baseWindow})
                dlg.open()
            }
        }
    }

    UiPanel{
        width: parent.width
        anchors.top: title.bottom; anchors.topMargin: 40; anchors.bottom: parent.bottom; anchors.bottomMargin: 0; anchors.left: parent.left; anchors.leftMargin: 0
        source : "image/n-panel-bg"

        RowLayout{
            id : listHeader
            height: 80
            anchors.top: parent.top; anchors.topMargin: 0; anchors.left: parent.left; anchors.leftMargin: 10; anchors.right: parent.right; anchors.rightMargin: 10
            spacing: 20

            Item{
                Layout.preferredWidth: 100
                Layout.preferredHeight: 1
                Layout.fillHeight: true
                Layout.fillWidth: true

                UiText{
                    height: 80;
                    anchors.top: parent.top; anchors.topMargin: 0; anchors.left: parent.left; anchors.leftMargin: 0; anchors.right: parent.right; anchors.rightMargin: 0

                    horizontalAlignment: Text.AlignHCenter; verticalAlignment: Text.AlignVCenter
                    text: panel.isRemoveUI ? "선택" : "순번"
                }
            }

            Item{
                Layout.preferredWidth: 200
                Layout.preferredHeight: 1
                Layout.fillHeight: true
                Layout.fillWidth: true

                UiText{
                    height: 80;
                    anchors.top: parent.top; anchors.topMargin: 0; anchors.left: parent.left; anchors.leftMargin: 0; anchors.right: parent.right; anchors.rightMargin: 0

                    horizontalAlignment: Text.AlignHCenter; verticalAlignment: Text.AlignVCenter
                    text:"제조번호"
                }
            }

            Item{
                Layout.preferredWidth: 200
                Layout.preferredHeight: 1
                Layout.fillHeight: true
                Layout.fillWidth: true

                UiText{
                    height: 80;
                    anchors.top: parent.top; anchors.topMargin: 0; anchors.left: parent.left; anchors.leftMargin: 0; anchors.right: parent.right; anchors.rightMargin: 0

                    horizontalAlignment: Text.AlignHCenter; verticalAlignment: Text.AlignVCenter
                    text:"부하"
                }
            }

            Item{
                Layout.preferredWidth: 200
                Layout.preferredHeight: 1
                Layout.fillHeight: true
                Layout.fillWidth: true

                UiText{
                    height: 80;
                    anchors.top: parent.top; anchors.topMargin: 0; anchors.left: parent.left; anchors.leftMargin: 0; anchors.right: parent.right; anchors.rightMargin: 0

                    horizontalAlignment: Text.AlignHCenter; verticalAlignment: Text.AlignVCenter
                    text:"무부하"
                }
            }

            Item{
                Layout.preferredWidth: 200
                Layout.preferredHeight: 1
                Layout.fillHeight: true
                Layout.fillWidth: true

                UiText{
                    height: 80;
                    anchors.top: parent.top; anchors.topMargin: 0; anchors.left: parent.left; anchors.leftMargin: 0; anchors.right: parent.right; anchors.rightMargin: 0

                    horizontalAlignment: Text.AlignHCenter; verticalAlignment: Text.AlignVCenter
                    text:"판정"
                }
            }
        }

        Rectangle{
            height: 2; width: listHeader.width - 40
            anchors.bottom: listHeader.bottom; anchors.horizontalCenter: listHeader.horizontalCenter

            color : "#9EAEC2"
        }

        ListView{
            id : reportList
            anchors.top: listHeader.bottom; anchors.topMargin: 0; anchors.bottom: cancelBtn.top; anchors.bottomMargin: 30; anchors.left: parent.left; anchors.leftMargin: 10; anchors.right: parent.right; anchors.rightMargin: 10
            clip: true;

            model : ListModel{
                id : listModel
            }

            delegate : ReportPanelItem{
                rowIdx : idx
                visibleCheckBox : panel.isRemoveUI
                reportModel :  panel.reportModel
            }
        }

        UiButton{
            id : cancelBtn
            height: 100; width: 240
            anchors.bottom: parent.bottom; anchors.bottomMargin: 30; anchors.right: removeBtn.left; anchors.rightMargin: 30
            textColor: "#9EAEC2"
            text: qsTr("취소")
            visible: panel.isRemoveUI

            norImage: "image/n-btn-bg.png"
            pressImage: "image/n-btn-press-bg.png"

            onClicked: {
                panel.isRemoveUI = false
            }
        }

        UiButton{
            id : removeBtn
            height: 100; width: 240
            anchors.bottom: parent.bottom; anchors.bottomMargin: 30; anchors.right: parent.right; anchors.rightMargin: 30
            textColor: "#9EAEC2"
            text: qsTr("삭제")
            visible: panel.isRemoveUI

            norImage: "image/n-btn-bg.png"
            pressImage: "image/n-btn-press-bg.png"

            onClicked: {
                var dlg = confirmBox.createObject(panel,{"messageText":"선택하신 이력을 삭제하시겠습니까?"})
                dlg.open()
            }
        }

        UiButton{
            id : usbSaveBtn
            height: 100; width: 240
            anchors.bottom: parent.bottom; anchors.bottomMargin: 30; anchors.right: selRemoveBtn.left; anchors.rightMargin: 30
            textColor: "#9EAEC2"
            text: qsTr("USB저장")
            visible: !panel.isRemoveUI

            norImage: "image/n-btn-bg.png"
            pressImage: "image/n-btn-press-bg.png"

            onClicked: {
                var dlg = usbSaveDlg.createObject(panel, {"baseWindow" : panel.baseWindow})
                dlg.open()
            }
        }

        UiButton{
            id : selRemoveBtn
            height: 100; width: 240
            anchors.bottom: parent.bottom; anchors.bottomMargin: 30; anchors.right: parent.right; anchors.rightMargin: 30
            textColor: "#9EAEC2"
            text: qsTr("선택 삭제")
            visible: !panel.isRemoveUI

            norImage: "image/n-btn-bg.png"
            pressImage: "image/n-btn-press-bg.png"

            onClicked: {
                panel.isRemoveUI = true
            }
        }
    }

    onIsRemoveUIChanged: {
        if(panel.isRemoveUI === false)
        {
            panel.reportModel.onCommandClearCheckList()
        }
    }

    Component{
        id : pdListDlg

        PDListDlg{
            onSignalEventNewProduct: {
                var dlg = pdSettingDlg.createObject(panel,{"oldPDNum":"", "baseWindow" : panel.baseWindow})
                dlg.open()
            }
        }
    }

    Component{
        id : pdSettingDlg

        PDSettingDlg{
        }
    }

    Component{
        id : usbSaveDlg

        USBSaveDlg{
        }
    }

    Component{
        id : confirmBox

        UiComfirmBox{
            onSignalEventConfirm: {
                panel.reportModel.onCommandRemoveCheckList()
                panel.isRemoveUI = false;
            }

            onSignalEventCancel: {
                panel.isRemoveUI = false;
            }
        }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
