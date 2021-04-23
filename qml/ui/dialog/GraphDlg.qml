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
import QmlDevPanelModel 1.0

UiDialog {
    id : dialog

    property QmlDevPanelModel devModel

    contentHeight: 1015; contentWidth: 1800
    anchors.centerIn : Overlay.overlay

    Component.onCompleted: {
        cycleCntGraph.startY = devModel.mGraphStartY;
        cycleCntGraph.yRange = devModel.mGraphEndY - devModel.mGraphStartY;
        rpmGraph.startY      = devModel.mGraphStartY;
        rpmGraph.yRange      = devModel.mGraphEndY - devModel.mGraphStartY;
        cycleCntGraph.xRange = devModel.mGraphXRange;
        rpmGraph.xRange      = devModel.mGraphXRange;

        minInput.text = ""+ devModel.mGraphStartY
        maxInput.text = ""+ devModel.mGraphEndY
        xRangeInput.text = "" + devModel.mGraphXRange

        cycleCntGraph.clearCanvas();
        cycleCntGraph.drawCanvas();
        rpmGraph.clearCanvas();
        rpmGraph.drawCanvas();
    }

    contentItem: Item{

        UiText{
            id : minLabel
            anchors.top: parent.top; anchors.topMargin: 80; anchors.left : parent.left; anchors.leftMargin: 20;
            height: 80; width: 100;
            verticalAlignment: Text.AlignVCenter
            text : "최소"
        }

        UiTextField{
            id : minInput
            width: 200
            anchors.verticalCenter: minLabel.verticalCenter; anchors.left: minLabel.right; anchors.leftMargin: 10
            labelText: "그래프 최소값"
            text: "0"
            inputType: QmlEnumDef.INT_MODE

            onSignalChangedValue: {
                labelText = value;
                var newStartY = parseInt(value)
                var newYRange = cycleCntGraph.startY  - newStartY + cycleCntGraph.yRange
                cycleCntGraph.startY = newStartY;
                cycleCntGraph.yRange = newYRange;
                rpmGraph.startY = newStartY
                rpmGraph.yRange = newYRange;

                cycleCntGraph.clearCanvas();
                cycleCntGraph.drawCanvas();
                rpmGraph.clearCanvas();
                rpmGraph.drawCanvas();

                devModel.onCommandSetGraphStartY(newStartY)
            }
        }

        UiText{
            id : maxLabel
            width: 100
            anchors.verticalCenter: minLabel.verticalCenter; anchors.left: minInput.right; anchors.leftMargin: 30
            verticalAlignment: Text.AlignVCenter
            text : "최대"
        }

        UiTextField{
            id : maxInput
            width: 200
            anchors.verticalCenter: minLabel.verticalCenter; anchors.left: maxLabel.right; anchors.leftMargin: 10
            labelText: "그래프 최대값"
            text: "0"
            inputType: QmlEnumDef.INT_MODE

            onSignalChangedValue: {
                labelText = value;
                var newEndY = parseInt(value)
                var newYRange = newEndY - cycleCntGraph.startY
                cycleCntGraph.yRange = newYRange;
                rpmGraph.yRange = newYRange;

                cycleCntGraph.clearCanvas();
                cycleCntGraph.drawCanvas();
                rpmGraph.clearCanvas();
                rpmGraph.drawCanvas();

                devModel.onCommandSetGraphEndY(newEndY)
            }
        }

        UiText{
            id : xRangeLabel
            width: 100
            anchors.verticalCenter: minLabel.verticalCenter; anchors.left: maxInput.right; anchors.leftMargin: 30
            verticalAlignment: Text.AlignVCenter
            text : "X축 시간"
        }

        UiTextField{
            id : xRangeInput
            width: 200
            anchors.verticalCenter: minLabel.verticalCenter; anchors.left: xRangeLabel.right; anchors.leftMargin: 10
            labelText: "x축 범위(ms)"
            text: "0"
            inputType: QmlEnumDef.INT_MODE

            onSignalChangedValue: {
                labelText = value;
                var xRange = parseInt(value)

                cycleCntGraph.xRange = xRange
                rpmGraph.xRange = xRange
                cycleCntGraph.clearCanvas();
                cycleCntGraph.drawCanvas();
                rpmGraph.clearCanvas();
                rpmGraph.drawCanvas();

                devModel.onCommandSetGraphXRange(xRange)
            }
        }

        UiCheck{
            height: 50; width: 50
            anchors.verticalCenter: minLabel.verticalCenter; anchors.left: xRangeInput.right; anchors.leftMargin: 30
            checked: false

            Component.onDestruction: {
                devModel.onCommandSetCycleCntGraphModel(null);
                devModel.onCommandSetRPMGraphModel(null);
            }


            onCheckedChanged: {
                if(checked)
                {
                    devModel.onCommandSetCycleCntGraphModel(cycleCntGraph.graphDataAlias);
                    devModel.onCommandSetRPMGraphModel(rpmGraph.graphDataAlias);

                    cycleCntGraph.clearCanvas();
                    cycleCntGraph.drawCanvas();
                    rpmGraph.clearCanvas();
                    rpmGraph.drawCanvas();
                }
                else
                {
                    devModel.onCommandSetCycleCntGraphModel(null);
                    devModel.onCommandSetRPMGraphModel(null);
                }
            }
        }

        LineFlowChart{
            id : cycleCntGraph
            anchors.top: minLabel.bottom; anchors.topMargin: 20; anchors.bottom: parent.bottom; anchors.bottomMargin: 100; anchors.left : parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 20
            yRange      : 20000 // senstivity * 2
            startY      : 0 // -1 * sensitivity
            xRange      : 100000
            lineColor   : "#0000FF"
            lineWidth   : 2
            yAxisAlias.yAxisItemFontSize: 20
            yAxisAlias.yAxisItemWidth : 100
            yAxisAlias.yAxisLineWidth : 1
            yAxisAlias.yAxisLineColor : "#4d707070"
            yAxisAlias.yAxisDivideCount: 10
        }

        LineFlowChart{
            id : rpmGraph
            anchors.top: minLabel.bottom; anchors.topMargin: 20; anchors.bottom: parent.bottom; anchors.bottomMargin: 100; anchors.left : parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 20
            yRange      : 20000 // senstivity * 2
            startY      : 0 // -1 * sensitivity
            xRange      : 100000
            lineColor   : "#FF0000"
            lineWidth   : 2
            yAxisAlias.yAxisItemFontSize: 20
            yAxisAlias.yAxisItemWidth : 100
            yAxisAlias.yAxisLineWidth : 1
            yAxisAlias.yAxisLineColor : "#4d707070"
            yAxisAlias.yAxisDivideCount: 10
        }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
