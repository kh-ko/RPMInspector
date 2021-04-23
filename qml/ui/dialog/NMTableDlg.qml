import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import QmlEnumDef 1.0
import EnumDef 1.0
import FontManager 1.0
import "../../control/"
import "../../control/chart/"
import "../../control/chart/linechart"
import "../image/"
import QmlPDSettingDlgModel 1.0

UiDialog {
    id : dialog

    property QmlPDSettingDlgModel settingModel

    contentHeight: 900; contentWidth: 700
    anchors.centerIn : Overlay.overlay

    contentItem: Item{

        Component.onCompleted: {
            settingModel.onCommandSetNMGraphModel(nmGraph.graphDataAlias)

            nmGraph.clearCanvas();
            nmGraph.drawCanvas();

            for(var i = 0; i <= 5; i ++)
            {
                var xValue = ((settingModel.mVolMax / 5) * i)
                var labelText = ""+Math.ceil(xValue)
                var xPosition = ""+(xAxis.width * ( xValue / settingModel.mVolMax))
                xLine.createObject(xAxis, {"xPosition" : xPosition, "labelText" : labelText})

                console.debug("x = " + xValue + ", position = " + xPosition)
            }
        }

        Item{
            id : xAxis
            anchors.top: parent.top; anchors.topMargin: 100; anchors.bottom: parent.bottom; anchors.bottomMargin: 180; anchors.left : parent.left; anchors.leftMargin: 120; anchors.right: parent.right; anchors.rightMargin: 20
        }
        LineFlowChart{
            id : nmGraph
            anchors.top: parent.top; anchors.topMargin: 100; anchors.bottom: parent.bottom; anchors.bottomMargin: 180; anchors.left : parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 20
            yRange      : settingModel.mNMMax
            startY      : 0
            xRange      : settingModel.mVolMax
            lineColor   : "#00FF00"
            lineWidth   : 2
            yAxisAlias.yAxisItemFontSize: 20
            yAxisAlias.yAxisItemWidth : 100
            yAxisAlias.yAxisLineWidth : 1
            yAxisAlias.yAxisLineColor : "#4d707070"
            yAxisAlias.yAxisDivideCount: 10
        }
    }

    Component{
        id : xLine

        Rectangle{
            property var xPosition
            property var labelText

            id : line
            x : xPosition
            width: 1
            anchors.top: parent.top; anchors.bottom: parent.bottom;

            color : "#4d707070"

            UiText{
                id : xValue
                anchors.top:parent.bottom; anchors.topMargin: 10; anchors.horizontalCenter: parent.horizontalCenter
                color: "#9e9e9e"
                font.pixelSize: 20
                font.bold  : false
                text : labelText
            }
        }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
