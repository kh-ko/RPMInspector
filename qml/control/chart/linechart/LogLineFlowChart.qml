import QtQuick 2.12
import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.3
import FontManager 1.0
import "./"
import "../"
import LineChartData 1.0
import LogLineChartData 1.0

Item {
    id : control

    property alias graphDataAlias : graphData
    property var   xRange         : 27
    property var   logBase        : 10
    property var   logStartExp    : -3
    property var   logEndExp      : 3
    property var   lineColor      : "#FF0000"
    property var   lineWidth      : 1
    property var   isRightYAxis   : false
    property alias yAxisAlias     : yAxis

    property LogLineCanvas currCanvas : null
    property LogLineCanvas preCanvas : null

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
        console.debug("[debug] LogLineFlowChart First draw --------------------------------------------------------------")

        if(graphData.mLastIdx < 0)
            return;

        if (control.currCanvas == null || ((control.currCanvas.startX + (control.currCanvas.xRange * 2)) <= graphData.onCommandGetXValue(graphData.mLastIdx) ) )
        {
            control.currCanvas = canvas01
            control.currCanvas.startX   =  graphData.onCommandGetXValue(graphData.mLastIdx) - control.xRange
            control.currCanvas.x = 0

            console.debug("[debug] First draw --------------------------------------------------------------")
            console.debug("[debug] currCanvas.startX        : " + currCanvas.startX)
            console.debug("[debug] currCanvas.x             : " + currCanvas.x)

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

            console.debug("[debug] Page change  -------------------------------------------------------------")
            console.debug("[debug] currCanvas.startX        : " + control.currCanvas.startX)
            console.debug("[debug] currCanvas.x             : " + control.currCanvas.x)
            console.debug("[debug] preCanvas.startX         : " + control.preCanvas.startX)
            console.debug("[debug] preCanvas.x              : " + control.preCanvas.x)
        }

        if(control.preCanvas !== null)
        {
            control.preCanvas.x = -1 * (control.preCanvas.width * ((graphData.onCommandGetXValue(graphData.mLastIdx) - (control.preCanvas.startX + control.preCanvas.xRange)) / control.preCanvas.xRange));
            currCanvas.x = preCanvas.x + preCanvas.width;

            console.debug("[debug]      Page move  ------------------------------------")
            console.debug("[debug]      currCanvas.x             : " + control.currCanvas.x)
            console.debug("[debug]      preCanvas.x              : " + control.preCanvas.x)
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

    LogLineChartData{
        id : graphData

        onSignalEventChangedLastIdx: { drawCanvas() }
    }


    onWidthChanged:  { clearCanvas(); timer.stop(); timer.start(); }
    onHeightChanged: { clearCanvas(); timer.stop(); timer.start(); }

    LogChartYAxis{
        id : yAxis

        anchors.fill: parent

        logBase     : control.logBase
        logStartExp : control.logStartExp
        logEndExp   : control.logEndExp
        isRightYAxis: control.isRightYAxis
    }

    Item{
        id : canvasViewPort

        anchors.top:parent.top; anchors.topMargin: 0; anchors.bottom: parent.bottom; anchors.bottomMargin: 0;
        anchors.left:parent.left; anchors.leftMargin: control.isRightYAxis ? 0 : yAxis.yAxisItemWidth; anchors.right: parent.right; anchors.rightMargin: control.isRightYAxis ? yAxis.yAxisItemWidth : 0

        clip: true

        LogLineCanvas{
            id : canvas01

            height: parent.height; width: parent.width
            anchors.verticalCenter: parent.verticalCenter

            graphData  : control.graphDataAlias
            xRange     : control.xRange
            logBase    : control.logBase
            logStartExp: control.logStartExp
            logEndExp  : control.logEndExp
            lineColor  : control.lineColor
            lineWidth  : control.lineWidth
        }

        LogLineCanvas{
            id : canvas02

            height: parent.height; width: parent.width
            anchors.verticalCenter: parent.verticalCenter

            graphData  : control.graphDataAlias
            xRange     : control.xRange
            logBase    : control.logBase
            logStartExp: control.logStartExp
            logEndExp  : control.logEndExp
            lineColor  : control.lineColor
            lineWidth  : control.lineWidth
        }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
