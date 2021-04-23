import QtQuick 2.12
import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.3
import FontManager 1.0
import "./"
import "../"
import LineChartData 1.0

Item {
    id : control

    property alias graphDataAlias : graphData
    property var   xRange         : 27
    property var   valueDivder    : 1
    property var   valueFixedN    : 0
    property var   yRange         : 100
    property var   startY         : 0
    property var   lineColor      : "#FF0000"
    property var   lineWidth      : 1

    property alias yAxisAlias     : yAxis

    property LineCanvas currCanvas : null
    property LineCanvas preCanvas : null


    function clearCanvas()
    {
        if(control.preCanvas != null)
        {
            control.preCanvas.clear()
            control.preCanvas = null
        }

        if(control.currCanvas != null)
        {
            control.currCanvas.clear()
            control.currCanvas = null
        }
    }

    function drawCanvas()
    {
        if(graphData.mLastIdx < 0)
            return;

        if (control.currCanvas == null || ((control.currCanvas.startX + (control.currCanvas.xRange * 2)) <= graphData.onCommandGetXValue(graphData.mLastIdx) ) )
        {
            control.currCanvas = canvas01
            control.currCanvas.startX   =  graphData.onCommandGetXValue(graphData.mLastIdx) - control.xRange
            control.currCanvas.x = 0

            if(control.preCanvas !== null)
            {
                control.preCanvas.clear()
                control.preCanvas = null
            }
        }

        if((control.currCanvas.startX + control.currCanvas.xRange) < graphData.onCommandGetXValue(graphData.mLastIdx))
        {
            var tempCanvase = control.preCanvas == null ? canvas02 : control.preCanvas
            control.preCanvas = control.currCanvas;
            control.currCanvas = tempCanvase;
            control.currCanvas.startX  = control.preCanvas.startX + control.preCanvas.xRange
        }

        if(control.preCanvas !== null)
        {
            control.preCanvas.x = -1 * (control.preCanvas.width * ((graphData.onCommandGetXValue(graphData.mLastIdx) - (control.preCanvas.startX + control.preCanvas.xRange)) / control.preCanvas.xRange));
            control.currCanvas.x = control.preCanvas.x + control.preCanvas.width;
        }

        if(control.preCanvas !== null)
        {
            control.preCanvas.drawLine();
        }

        control.currCanvas.drawLine();
    }

    Timer{
        id : timer
        interval: 1000; running: false; repeat: false
        onTriggered:
        {
            clearCanvas(); drawCanvas()
        }
    }

    onWidthChanged:  { clearCanvas(); timer.stop(); timer.start(); }
    onHeightChanged: { clearCanvas(); timer.stop(); timer.start(); }

    LineChartData{
        id : graphData

        onSignalEventChangedLastIdx: { drawCanvas() }
    }


    ChartYAxis{
        id : yAxis

        anchors.fill: parent

        valueDivder    : control.valueDivder
        valueFixedN    : control.valueFixedN
        valueRange     : control.yRange
        startValue     : control.startY
    }

    Item{
        id : canvasViewPort

        anchors.top:parent.top; anchors.topMargin: 0; anchors.bottom: parent.bottom; anchors.bottomMargin: 0; anchors.left:parent.left; anchors.leftMargin: yAxis.yAxisItemWidth; anchors.right: parent.right; anchors.rightMargin: 0

        clip: true

        LineCanvas{
            id : canvas01

            height: parent.height; width: parent.width
            anchors.verticalCenter: parent.verticalCenter

            graphData : control.graphDataAlias
            xRange    : control.xRange
            startY    : control.startY
            yRange    : control.yRange
            lineColor : control.lineColor
            lineWidth : control.lineWidth
        }

        LineCanvas{
            id : canvas02

            height: parent.height; width: parent.width
            anchors.verticalCenter: parent.verticalCenter

            graphData : control.graphDataAlias
            xRange    : control.xRange
            startY    : control.startY
            yRange    : control.yRange
            lineColor : control.lineColor
            lineWidth : control.lineWidth
        }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
