import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import QmlEnumDef 1.0
import EnumDef 1.0
import FontManager 1.0
import "../../control/"
import "../image/"
import QmlPDSettingDlgModel 1.0

UiDialog {
    id : dialog

    property var baseWindow : null
    property var oldPDNum : ""

    contentHeight: 1015; contentWidth: 800
    anchors.centerIn : parent

    QmlPDSettingDlgModel{
        id : settingModel

        Component.onCompleted: {
            settingModel.onCommandLoadPDSetting(dialog.oldPDNum)
        }
    }

    contentItem: Item{
        Item{
            id : titleBox
            height: 80; width: parent.width
            anchors.top: parent.top; anchors.horizontalCenter: parent.horizontalCenter

            UiText{
                anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.left; anchors.leftMargin : 20

                text: "제품 설정"
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
                            id : pdModelLabel
                            width: 270
                            anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.left
                            text: "제품 모델"
                        }

                        UiTextField{
                            width: 350
                            anchors.verticalCenter: parent.verticalCenter; anchors.left: pdModelLabel.right; anchors.leftMargin: 10
                            labelText: pdModelLabel.text
                            text: settingModel.mModel
                            inputType: QmlEnumDef.STRING_MODE

                            onSignalChangedValue: {
                                settingModel.onCommandSetModel(value)
                            }
                        }
                    }

                    Item{
                        Layout.preferredHeight: 1; Layout.preferredWidth: 1; Layout.fillHeight: true; Layout.fillWidth: true

                        UiText{
                            id : pdNumLabel
                            width: 270
                            anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.left
                            text: "제품 번호"
                        }

                        UiTextField{
                            width: 350
                            anchors.verticalCenter: parent.verticalCenter; anchors.left: pdNumLabel.right; anchors.leftMargin: 10
                            labelText: pdNumLabel.text
                            text: settingModel.mPDNum
                            inputType: QmlEnumDef.INT_MODE

                            onSignalChangedValue: {
                                settingModel.onCommandSetPDNum(value)
                            }
                        }
                    }

                    Item{
                        Layout.preferredHeight: 1; Layout.preferredWidth: 1; Layout.fillHeight: true; Layout.fillWidth: true

                        UiText{
                            id : pdNameLabel
                            width: 270
                            anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.left
                            text: "제품명"
                        }

                        UiTextField{
                            width: 350
                            anchors.verticalCenter: parent.verticalCenter; anchors.left: pdNameLabel.right; anchors.leftMargin: 10
                            labelText: pdNameLabel.text
                            text: settingModel.mPDName
                            inputType: QmlEnumDef.STRING_MODE

                            onSignalChangedValue: {
                                settingModel.onCommandSetPDName(value)
                            }
                        }
                    }
/*
                    Item{
                        Layout.preferredHeight: 1; Layout.preferredWidth: 1; Layout.fillHeight: true; Layout.fillWidth: true

                        UiText{
                            id : pdRatingLabel
                            width: 270
                            anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.left
                            text: "정격 RPM"
                        }

                        UiTextField{
                            width: 350
                            anchors.verticalCenter: parent.verticalCenter; anchors.left: pdRatingLabel.right; anchors.leftMargin: 10
                            labelText: pdRatingLabel.text
                            text: ""+settingModel.mRatedRPM

                            onSignalChangedValue: {
                                var intValue = parseInt(value)
                                settingModel.onCommandSetRatedRPM(intValue)
                            }
                        }
                    }*/
                }
            }

            UiGroupBox{
                id : loadGroupBox
                Layout.preferredHeight: 285; Layout.preferredWidth: 1; Layout.fillHeight: true; Layout.fillWidth: true
                titleText.text: "부하"

                ColumnLayout{
                    width: parent.width - 40
                    anchors.top: loadGroupBox.titleBox.bottom; anchors.topMargin: 10; anchors.bottom: parent.bottom; anchors.bottomMargin: 10; anchors.horizontalCenter: parent.horizontalCenter
                    spacing: 20;

                    Item{
                        Layout.preferredHeight: 1; Layout.preferredWidth: 1; Layout.fillHeight: true; Layout.fillWidth: true

                        UiText{
                            id : loadTimeLabel
                            width: 270
                            anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.left
                            text: "검사 시간(초)"
                        }

                        UiTextField{
                            width: 350
                            anchors.verticalCenter: parent.verticalCenter; anchors.left: loadTimeLabel.right; anchors.leftMargin: 10
                            labelText: loadTimeLabel.text
                            text: ""+Math.round(settingModel.mLoadMeasureTime/1000)

                            onSignalChangedValue: {
                                var intValue = parseInt(value)
                                settingModel.onCommandSetLoadMeasureTime(intValue * 1000)
                            }
                        }
                    }

                    Item{
                        Layout.preferredHeight: 1; Layout.preferredWidth: 1; Layout.fillHeight: true; Layout.fillWidth: true

                        UiText{
                            id : loadConditionLabel
                            width: 270
                            anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.left
                            text: "합격 조건(RPM)"
                        }

                        UiTextField{
                            id : inputLoadCondition
                            width: 350
                            anchors.verticalCenter: parent.verticalCenter; anchors.left: loadConditionLabel.right; anchors.leftMargin: 10
                            labelText: loadConditionLabel.text
                            text: ""+settingModel.mLoadCondition

                            onSignalChangedValue: {
                                var intValue = parseInt(value)
                                settingModel.onCommandSetLoadCondition(intValue)
                            }
                        }

                        UiText{
                            width: 70
                            anchors.verticalCenter: parent.verticalCenter; anchors.left: inputLoadCondition.right; anchors.leftMargin: 10
                            text: "이상"
                        }
                    }

                    Item{
                        Layout.preferredHeight: 1; Layout.preferredWidth: 1; Layout.fillHeight: true; Layout.fillWidth: true

                        UiText{
                            id : loadConditionNMLabel
                            width: 270
                            anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.left
                            text: "부하량(kgfcm)"

                            MouseArea{
                                anchors.fill: parent

                                onClicked: {
                                    var dlg = nmChartDlg.createObject(loadConditionNMLabel, {"settingModel": settingModel})
                                    dlg.open()
                                }
                            }
                        }

                        UiTextField{
                            id : inputLoadConditionNM
                            width: 350
                            anchors.verticalCenter: parent.verticalCenter; anchors.left: loadConditionNMLabel.right; anchors.leftMargin: 10
                            labelText: loadConditionNMLabel.text
                            text: ""+ (settingModel.mLoadNM / 1000)
                            inputType : QmlEnumDef.FLOAT_MODE
                            onSignalChangedValue: {
                                var floatValue = Math.round(parseFloat(value) * 1000);
                                settingModel.onCommandSetLoadNM(floatValue)
                            }
                        }
                    }
                }
            }

            UiGroupBox{
                id : nonLoadGroupBox
                Layout.preferredHeight: 205; Layout.preferredWidth: 1; Layout.fillHeight: true; Layout.fillWidth: true
                titleText.text: "무부하"

                ColumnLayout{
                    width: parent.width - 40
                    anchors.top: nonLoadGroupBox.titleBox.bottom; anchors.topMargin: 10; anchors.bottom: parent.bottom; anchors.bottomMargin: 10; anchors.horizontalCenter: parent.horizontalCenter
                    spacing: 20;

                    Item{
                        Layout.preferredHeight: 1; Layout.preferredWidth: 1; Layout.fillHeight: true; Layout.fillWidth: true

                        UiText{
                            id : nonLoadTimeLabel
                            width: 270
                            anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.left
                            text: "검사 시간(초)"
                        }

                        UiTextField{
                            width: 350
                            anchors.verticalCenter: parent.verticalCenter; anchors.left: nonLoadTimeLabel.right; anchors.leftMargin: 10
                            labelText: nonLoadTimeLabel.text
                            text: ""+Math.round(settingModel.mNonLoadMeasureTime/1000)

                            onSignalChangedValue: {
                                var intValue = parseInt(value)
                                settingModel.onCommandSetNonLoadMeasureTime(intValue * 1000)
                            }
                        }
                    }

                    Item{
                        Layout.preferredHeight: 1; Layout.preferredWidth: 1; Layout.fillHeight: true; Layout.fillWidth: true

                        UiText{
                            id : nonLoadConditionLabel
                            width: 270
                            anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.left
                            text: "합격 조건(RPM)"
                        }

                        UiTextField{
                            id : inputNonLoadConditionFrom
                            width: 150
                            anchors.verticalCenter: parent.verticalCenter; anchors.left: nonLoadConditionLabel.right; anchors.leftMargin: 10
                            labelText: nonLoadConditionLabel.text + "(부터)"
                            text: ""+settingModel.mNonLoadConditionFrom

                            onSignalChangedValue: {
                                var intValue = parseInt(value)
                                settingModel.onCommandSetNonLoadConditionFrom(intValue)
                            }
                        }

                        UiText{
                            id : nonLoadConditionFromLabel
                            width: 30
                            anchors.verticalCenter: parent.verticalCenter; anchors.left: inputNonLoadConditionFrom.right; anchors.leftMargin: 10
                            text: "~"
                        }

                        UiTextField{
                            id : inputNonLoadConditionTo
                            width: 150
                            anchors.verticalCenter: parent.verticalCenter; anchors.left: nonLoadConditionFromLabel.right; anchors.leftMargin: 10
                            labelText: nonLoadConditionLabel.text + "(까지)"
                            text: ""+settingModel.mNonLoadConditionTo

                            onSignalChangedValue: {
                                var intValue = parseInt(value)
                                settingModel.onCommandSetNonLoadConditionTo(intValue)
                            }
                        }

                        UiText{
                            width: 70
                            anchors.verticalCenter: parent.verticalCenter; anchors.left: inputNonLoadConditionTo.right; anchors.leftMargin: 10
                            text: "이상"
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
                    var ret = settingModel.onCommandApply()

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

    Component{
        id : nmChartDlg

        NMTableDlg{
        }
    }
}
