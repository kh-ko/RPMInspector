import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import QmlEnumDef 1.0
import EnumDef 1.0
import FontManager 1.0
import "../../control/"
import "../image/"
import QmlMeasureCfgDlgModel 1.0

UiDialog {
    id : dialog

    contentHeight: 1015; contentWidth: 800
    anchors.centerIn : parent


    QmlMeasureCfgDlgModel{
        id : cfgModel
    }

    contentItem: Item{
        Item{
            id : titleBox
            height: 80; width: parent.width
            anchors.top: parent.top; anchors.horizontalCenter: parent.horizontalCenter

            UiText{
                anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.left; anchors.leftMargin : 20

                text: "측정 고급 설정"
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

            Item{
                Layout.preferredHeight: 1; Layout.preferredWidth: 1; Layout.fillHeight: true; Layout.fillWidth: true

                UiText{
                    id : chuckDelayLabel
                    width: 200
                    anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.left
                    text: "척 지연시간"
                }

                UiTextField{
                    id : inputChuckDelay
                    width: 400
                    anchors.verticalCenter: parent.verticalCenter; anchors.left: chuckDelayLabel.right; anchors.leftMargin: 10
                    text: "" + cfgModel.mChuckRunDelayTime

                    onSignalChangedValue: {
                        var intValue = parseInt(value)
                        cfgModel.onCommandSetChuckRunDelayTime(intValue)
                    }
                }

                UiText{
                    id : chuckDelayPostFix
                    anchors.verticalCenter: parent.verticalCenter; anchors.left: inputChuckDelay.right
                    text: "ms"
                }
            }

            Item{
                Layout.preferredHeight: 1; Layout.preferredWidth: 1; Layout.fillHeight: true; Layout.fillWidth: true

                UiText{
                    id : valveDelayLabel
                    width: 200
                    anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.left
                    text: "벨브 지연시간"
                }

                UiTextField{
                    id : inputValveDelay
                    width: 400
                    anchors.verticalCenter: parent.verticalCenter; anchors.left: valveDelayLabel.right; anchors.leftMargin: 10
                    text: "" + cfgModel.mValveRunDelayTime

                    onSignalChangedValue: {
                        var intValue = parseInt(value)
                        cfgModel.onCommandSetValveRunDelayTime(intValue)
                    }
                }

                UiText{
                    id : valveDelayPostFix
                    anchors.verticalCenter: parent.verticalCenter; anchors.left: inputValveDelay.right
                    text: "ms"
                }
            }

            Item{
                Layout.preferredHeight: 1; Layout.preferredWidth: 1; Layout.fillHeight: true; Layout.fillWidth: true

                UiText{
                    id : voltageDelayLabel
                    width: 200
                    anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.left
                    text: "전압 지연시간"
                }

                UiTextField{
                    id : inputVoltageDelay
                    width: 400
                    anchors.verticalCenter: parent.verticalCenter; anchors.left: voltageDelayLabel.right; anchors.leftMargin: 10
                    text: "" + cfgModel.mVoltageSetDelayTime

                    onSignalChangedValue: {
                        var intValue = parseInt(value)
                        cfgModel.onCommandSetVoltageSetDelayTime(intValue)
                    }
                }

                UiText{
                    id : voltageDelayPostFix
                    anchors.verticalCenter: parent.verticalCenter; anchors.left: inputVoltageDelay.right
                    text: "ms"
                }
            }

            Item{
                Layout.preferredHeight: 1; Layout.preferredWidth: 1; Layout.fillHeight: true; Layout.fillWidth: true

                UiText{
                    id : loadDelayLabel
                    width: 200
                    anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.left
                    text: "부하 지연시간"
                }

                UiTextField{
                    id : inputLoadDelay
                    width: 400
                    anchors.verticalCenter: parent.verticalCenter; anchors.left: loadDelayLabel.right; anchors.leftMargin: 10
                    text: "" + cfgModel.mLoadMeasureDelayTime

                    onSignalChangedValue: {
                        var intValue = parseInt(value)
                        cfgModel.onCommandSetLoadMeasureDelayTime(intValue)
                    }
                }

                UiText{
                    id : loadDelayPostFix
                    anchors.verticalCenter: parent.verticalCenter; anchors.left: inputLoadDelay.right
                    text: "ms"
                }
            }

            Item{
                Layout.preferredHeight: 1; Layout.preferredWidth: 1; Layout.fillHeight: true; Layout.fillWidth: true

                UiText{
                    id : nonLoadDelayLabel
                    width: 200
                    anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.left
                    text: "무부하 지연시간"
                }

                UiTextField{
                    id : inputNonLoadDelay
                    width: 400
                    anchors.verticalCenter: parent.verticalCenter; anchors.left: nonLoadDelayLabel.right; anchors.leftMargin: 10
                    text: "" + cfgModel.mNonLoadMeasureDelayTime

                    onSignalChangedValue: {
                        var intValue = parseInt(value)
                        cfgModel.onCommandSetNonLoadMeasureDelayTime(intValue)
                    }
                }

                UiText{
                    id : nonLoadDelayPostFix
                    anchors.verticalCenter: parent.verticalCenter; anchors.left: inputNonLoadDelay.right
                    text: "ms"
                }
            }

            Item{
                Layout.preferredHeight: 1; Layout.preferredWidth: 1; Layout.fillHeight: true; Layout.fillWidth: true

                UiText{
                    id : measureAvgLabel
                    width: 200
                    anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.left
                    text: "평균계산시간"
                }

                UiTextField{
                    id : inputMeasureAvg
                    width: 400
                    anchors.verticalCenter: parent.verticalCenter; anchors.left: measureAvgLabel.right; anchors.leftMargin: 10
                    text: "" + cfgModel.mMeasureAvgRange

                    onSignalChangedValue: {
                        var intValue = parseInt(value)
                        cfgModel.onCommandSetMeasureAvgRange(intValue)
                    }
                }

                UiText{
                    id : measureAvgPostFix
                    anchors.verticalCenter: parent.verticalCenter; anchors.left: inputMeasureAvg.right
                    text: "ms"
                }
            }

            Item{
                Layout.preferredHeight: 1; Layout.preferredWidth: 1; Layout.fillHeight: true; Layout.fillWidth: true

                UiText{
                    id : kgfcmGainLabel
                    width: 200
                    anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.left
                    text: "kgf.cm 변환률"
                }

                UiTextField{
                    id : inputkgfcmGain
                    width: 400
                    anchors.verticalCenter: parent.verticalCenter; anchors.left: kgfcmGainLabel.right; anchors.leftMargin: 10
                    text: "" + cfgModel.mKgfcmGain
                    inputType : QmlEnumDef.FLOAT_MODE

                    onSignalChangedValue: {
                        var floatValue = parseFloat(value)
                        cfgModel.onCommandSetKgfcmGain(floatValue)
                    }
                }
            }

            Item{
                Layout.preferredHeight: 1; Layout.preferredWidth: 1; Layout.fillHeight: true; Layout.fillWidth: true

                UiText{
                    id : rtAdjVoltageLabel
                    width: 200
                    anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.left
                    text: "실시간 전압추적"
                }

                UiRadio{
                    id : rtAdjVoltageRadio
                    height: 50; width: 50;
                    anchors.verticalCenter: parent.verticalCenter; anchors.left: rtAdjVoltageLabel.right; anchors.leftMargin: 10

                    checkable: false
                    checked: cfgModel.mIsRtAdjVoltage
                }

                MouseArea{
                    anchors.fill: parent

                    onClicked: {
                        cfgModel.onCommandSetIsRtAdjVoltage(!cfgModel.mIsRtAdjVoltage)
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
                    cfgModel.onCommandApply()
                    dialog.close();
                }
            }
        }
    }
}
