import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import QmlEnumDef 1.0
import EnumDef 1.0
import FontManager 1.0
import "../../control/"
import "../image/"
import QmlUSBSaveDlgModel 1.0

UiDialog {
    id : dialog

    property var baseWindow : null

    contentHeight: 400; contentWidth: 700
    anchors.centerIn : parent

    closePolicy: Popup.NoAutoClose

    QmlUSBSaveDlgModel{
        id : usbSaveModel

        onSignalEventCopyFail: {
            baseWindow.showToast("이력을 복사중 오류가 발생하였습니다.")
        }

        onSignalEventFileNotSearch: {
            baseWindow.showToast("해당 이력이 존재하지 않습니다.")
        }

        onSignalEventUSBNotSearch: {
            baseWindow.showToast("USB가 인식되지 않습니다.")
        }
    }

    contentItem: Item{
        Item{
            id : titleBox
            height: 80; width: parent.width
            anchors.top: parent.top; anchors.horizontalCenter: parent.horizontalCenter

            UiText{
                anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.left; anchors.leftMargin : 20

                text: "USB저장"
            }

            UiButton{
                height: 52; width: 52
                anchors.verticalCenter: parent.verticalCenter; anchors.right: parent.right; anchors.rightMargin: 20

                norImage: "/ui/image/close-btn-bg.png"
                pressImage: "/ui/image/close-btn-press-bg.png"

                onClicked: {
                    dialog.close();
                }
            }
        }

        Item{
            width: parent.width - 60
            anchors.top: titleBox.bottom; anchors.topMargin: 20; anchors.bottom: footBox.top; anchors.bottomMargin: 20; anchors.horizontalCenter: parent.horizontalCenter

            Item{
                id : dateInputBox
                anchors.fill: parent
                visible: usbSaveModel.mSaveStep === QmlEnumDef.USBSAVE_STEP_NONE

                UiTextField{
                    id : yearInput
                    width: 150
                    anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.left; anchors.leftMargin: 30

                    labelText: "년도 입력"
                    text: ""+usbSaveModel.mFromYear

                    onSignalChangedValue: {
                        var intValue = parseInt(value)
                        usbSaveModel.onCommandSetFromYear(intValue)
                    }
                }

                UiText{
                    id : yearPostLabel
                    anchors.verticalCenter: parent.verticalCenter; anchors.left: yearInput.right; anchors.leftMargin: 10
                    text: "년"
                }

                UiTextField{
                    id : monthInput
                    width: 150
                    anchors.verticalCenter: parent.verticalCenter; anchors.left: yearPostLabel.right; anchors.leftMargin: 20

                    labelText: "월 입력"
                    text: ""+usbSaveModel.mFromMonth

                    onSignalChangedValue: {
                        var intValue = parseInt(value)
                        usbSaveModel.onCommandSetFromMonth(intValue)
                    }
                }

                UiText{
                    id : monthPostLabel
                    anchors.verticalCenter: parent.verticalCenter; anchors.left: monthInput.right; anchors.leftMargin: 10
                    text: "월 이력부터 저장"
                }
            }

            Item{
                anchors.fill: parent
                visible: usbSaveModel.mSaveStep === QmlEnumDef.USBSAVE_STEP_SCAN

                BusyIndicator{
                    id : scanningBusyBox
                    height: 50; width: 50
                    anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.left; anchors.leftMargin: 30
                    running: true
                }

                UiText{
                    anchors.verticalCenter: parent.verticalCenter; anchors.left: scanningBusyBox.right; anchors.leftMargin: 20
                    text: "USB 검색중입니다."
                }
            }

            Item{
                anchors.fill: parent
                visible: usbSaveModel.mSaveStep === QmlEnumDef.USBSAVE_STEP_COPY

                UiText{
                    id : copyStateLabel
                    anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.left; anchors.leftMargin: 100
                    text: "이력 복사중입니다. (" +usbSaveModel.mProgressCnt + "/" + usbSaveModel.mTotalCnt + ")"
                }

                ProgressBar{
                    height: 10; width: parent.width - 60
                    anchors.top: copyStateLabel.bottom; anchors.topMargin: 20; anchors.horizontalCenter: parent.horizontalCenter

                    value: usbSaveModel.mProgressCnt
                    to: usbSaveModel.mTotalCnt
                }
            }

            Item{
                id : completeMsgBox
                anchors.fill: parent
                visible: usbSaveModel.mSaveStep === QmlEnumDef.USBSAVE_STEP_COMPLETE

                UiText{
                    anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.left; anchors.leftMargin: 30
                    text: "복사가 완료 되었습니다. USB를 분리해 주세요."
                }
            }
        }

        Item{
            id : footBox
            height: 80; width: parent.width
            anchors.bottom: parent.bottom; anchors.horizontalCenter: parent.horizontalCenter

            UiButton{
                id : confirmBtn
                height: 70; width: 200
                anchors.verticalCenter: parent.verticalCenter; anchors.horizontalCenter: parent.horizontalCenter
                visible: completeMsgBox.visible

                norImage: "/ui/image/btn-bg.png"
                pressImage: "/ui/image/btn-press-bg.png"

                text: "완료"

                onClicked: {
                    dialog.close();
                }
            }

            UiButton{
                height: 70; width: 200
                anchors.verticalCenter: parent.verticalCenter; anchors.horizontalCenter: parent.horizontalCenter
                visible: dateInputBox.visible

                norImage: "/ui/image/btn-bg.png"
                pressImage: "/ui/image/btn-press-bg.png"

                text: "저장"

                onClicked: {
                    usbSaveModel.onCommandSave()
                }
            }
        }
    }
}
