import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import QmlEnumDef 1.0
import EnumDef 1.0
import FontManager 1.0
import "../../control/"
import "../image/"
import QmlWriterInfoDlgModel 1.0

UiDialog {
    id : dialog

    property var baseWindow : null
    property var oldPDNum : ""

    contentHeight: 400; contentWidth: 800
    anchors.centerIn : parent

    QmlWriterInfoDlgModel{
        id : writerInfoModel
    }

    contentItem: Item{
        Item{
            id : titleBox
            height: 80; width: parent.width
            anchors.top: parent.top; anchors.horizontalCenter: parent.horizontalCenter

            UiText{
                anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.left; anchors.leftMargin : 20

                text: "작성 정보"
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

        ColumnLayout{
            width: parent.width - 60
            anchors.top: titleBox.bottom; anchors.topMargin: 20; anchors.bottom: footBox.top; anchors.bottomMargin: 20; anchors.horizontalCenter: parent.horizontalCenter
            spacing: 20;

            UiGroupBox{
                id : norGroupBox
                Layout.preferredHeight: 365; Layout.preferredWidth: 1; Layout.fillHeight: true; Layout.fillWidth: true
                titleText.text: "일반"

                ColumnLayout{
                    width: parent.width - 40
                    anchors.top: norGroupBox.titleBox.bottom; anchors.topMargin: 10; anchors.bottom: parent.bottom; anchors.bottomMargin: 10; anchors.horizontalCenter: parent.horizontalCenter
                    spacing: 20;

                    Item{
                        Layout.preferredHeight: 1; Layout.preferredWidth: 1; Layout.fillHeight: true; Layout.fillWidth: true

                        UiText{
                            id : writerLabel
                            width: 270
                            anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.left
                            text: "작성자"
                        }

                        UiTextField{
                            width: 350
                            anchors.verticalCenter: parent.verticalCenter; anchors.left: writerLabel.right; anchors.leftMargin: 10
                            labelText: writerLabel.text
                            text: writerInfoModel.mWriter
                            inputType: QmlEnumDef.STRING_MODE

                            onSignalChangedValue: {
                                writerInfoModel.onCommandSetWriter(value)
                            }
                        }
                    }

                    Item{
                        Layout.preferredHeight: 1; Layout.preferredWidth: 1; Layout.fillHeight: true; Layout.fillWidth: true

                        UiText{
                            id : writeDateLabel
                            width: 270
                            anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.left
                            text: "작성 일자"
                        }

                        RowLayout{
                            height: parent.height; width: 350
                            anchors.verticalCenter: parent.verticalCenter; anchors.left: writeDateLabel.right; anchors.leftMargin: 10
                            spacing: 10;

                            UiTextField{
                                Layout.preferredHeight: 35; Layout.preferredWidth: 4; Layout.fillWidth: true
                                labelText: "작성 년"
                                text: writerInfoModel.mWriteYear
                                inputType: QmlEnumDef.INT_MODE

                                onSignalChangedValue: {
                                    writerInfoModel.onCommandSetWriteYear(value)
                                }
                            }

                            UiText{
                                Layout.preferredHeight: 35; Layout.preferredWidth: 1; Layout.fillWidth: true
                                text: "년"
                            }

                            UiTextField{
                                Layout.preferredHeight: 35; Layout.preferredWidth: 2; Layout.fillWidth: true
                                labelText: "작성 월"
                                text: writerInfoModel.mWriteMonth
                                inputType: QmlEnumDef.INT_MODE

                                onSignalChangedValue: {
                                    writerInfoModel.onCommandSetWriteMonth(value)
                                }
                            }

                            UiText{
                                Layout.preferredHeight: 35; Layout.preferredWidth: 1; Layout.fillWidth: true
                                text: "월"
                            }

                            UiTextField{
                                Layout.preferredHeight: 35; Layout.preferredWidth: 2; Layout.fillWidth: true
                                labelText: "작성 일"
                                text: writerInfoModel.mWriteDay
                                inputType: QmlEnumDef.INT_MODE

                                onSignalChangedValue: {
                                    writerInfoModel.onCommandSetWriteDay(value)
                                }
                            }

                            UiText{
                                Layout.preferredHeight: 35; Layout.preferredWidth: 1; Layout.fillWidth: true
                                text: "일"
                            }

                        }
                    }
                }
            }
        }

        Item{
            id : footBox
            height: 80; width: parent.width
            anchors.bottom: parent.bottom; anchors.horizontalCenter: parent.horizontalCenter

            UiButton{
                height: 70; width: 200
                anchors.verticalCenter: parent.verticalCenter; anchors.horizontalCenter: parent.horizontalCenter

                norImage: "/ui/image/btn-bg.png"
                pressImage: "/ui/image/btn-press-bg.png"

                text: "적용"

                onClicked: {
                    var ret = writerInfoModel.onCommandApply()

                    if(ret !== "" && baseWindow !== null)
                    {
                        baseWindow.showToast(ret)
                        return;
                    }

                    baseWindow.showToast("설정이 적용 되었습니다.")
                    dialog.close();
                }
            }
        }
    }
}
