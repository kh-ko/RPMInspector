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

Item{
    id : rowItem

    property int rowIdx
    property var visibleCheckBox : false
    property QmlReportModel reportModel : null

    height: 80; width: parent.width

    states: State {
        name: "visibleCheckBox"; when: rowItem.visibleCheckBox
        PropertyChanges { target: checkBox; x: 0}
    }

    transitions: Transition {
        to : "visibleCheckBox"
        reversible: true
        PropertyAnimation { property: "x"; duration: 250 }
    }

    Rectangle{
        height: 1; width: parent.width - 40
        anchors.bottom: parent.bottom; anchors.horizontalCenter: parent.horizontalCenter

        color : "#999EAEC2"
    }

    onVisibleCheckBoxChanged: {

        if(visibleCheckBox)
            checkBtn.checked = reportModel.onCommandIsCheck(rowItem.rowIdx)
    }

    RowLayout{
        anchors.fill: parent
        spacing: 20

        Item{

            Layout.preferredWidth: 100; Layout.preferredHeight: 1; Layout.fillHeight: true; Layout.fillWidth: true
            clip: true

            Item{
                id : checkBox
                height: parent.height; width: parent.width; x : (-1 * width); y : 0

                UiCheck{
                    id : checkBtn
                    height: 80; width:80; anchors.verticalCenter: parent.verticalCenter; anchors.horizontalCenter: parent.horizontalCenter
                    checkable: false;
                    checked: reportModel.onCommandIsCheck(rowItem.rowIdx)

                    onClicked: {
                        reportModel.onCommandToggleCheck(rowItem.rowIdx)
                        checked = reportModel.onCommandIsCheck(rowItem.rowIdx)
                    }
                }
            }

            UiText{
                height: 80; width: parent.width
                anchors.verticalCenter: parent.verticalCenter; anchors.left: checkBox.right; anchors.leftMargin: 0

                horizontalAlignment: Text.AlignHCenter; verticalAlignment: Text.AlignVCenter
                text:reportModel.onCommandGetSeq(rowItem.rowIdx)
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
                text:reportModel.onCommandGetPDSeq(rowItem.rowIdx)
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
                text:reportModel.onCommandGetLoadRPM(rowItem.rowIdx)
                color : "#3F464E"
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
                text:reportModel.onCommandGetNonLoadRPM(rowItem.rowIdx)
                color : "#3F464E"
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
                text:reportModel.onCommandGetJudg(rowItem.rowIdx)
                color : "#3F464E"
            }
        }
    }
}



/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
