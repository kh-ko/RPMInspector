import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import LineChartData 1.0

Canvas {
    id : canvas

    property var graphData     : null
    property var lineColor
    property var lineWidth
    property var logBase
    property var logStartExp
    property var logEndExp
    property var xRange
    property var startX

    property var startLogY
    property var logYRange
    property var lastPaintIdx

    renderTarget : Canvas.FramebufferObject

    function log(val)
    {
        return Math.log(val) / Math.log(canvas.logBase);
    }

    function clear()
    {
        if(graphData === null || canvas.available === false)
            return;

        var ctx = getContext("2d");
        ctx.reset();
        ctx.lineWidth = canvas.lineWidth
        ctx.strokeStyle = canvas.lineColor //"#0085FF"
        ctx.fillStyle = "#00000000"
        ctx.lineCap = "round"

        ctx.beginPath()

        canvas.startLogY = log((Math.pow(canvas.logBase, canvas.logStartExp)))
        canvas.logYRange =log(Math.pow(canvas.logBase, canvas.logEndExp)) - canvas.startLogY;

        canvas.lastPaintIdx = graphData.onCommandGetNearMinIdx(canvas.startX) - 1;

        console.debug("[debug]          clear ------------------------------------")
        console.debug("[debug]          lastPaintIdx             : " + canvas.lastPaintIdx)
        console.debug("[debug]          startLogY                : " + canvas.startLogY)
        console.debug("[debug]          logYRange                : " + canvas.logYRange)

        canvas.requestPaint();
    }

    function drawLine()
    {
        if(graphData === null || canvas.available === false)
            return;

        if(graphData.mLastIdx < 0)
            return;

        var ctx = canvas.getContext("2d")

        var drawStartIdx = canvas.lastPaintIdx + 1;

        console.debug("[debug]          drawLine ------------------------------------")
        console.debug("[debug]          drawStartIdx             : " + drawStartIdx)

        for(var i = drawStartIdx; ; i ++)
        {
            if( i > canvas.graphData.mLastIdx)
                break;

            var xValue = canvas.graphData.onCommandGetXValue(i);
            var yValue = canvas.graphData.onCommandGetYValue(i);
            var yLogValue = log(yValue)

            var xPosition = (canvas.width * ((xValue - canvas.startX) / canvas.xRange))
            var yPosition = canvas.height - (canvas.height * ((yLogValue - canvas.startLogY) / canvas.logYRange))

            console.debug("[debug]          i                        : " + i)
            console.debug("[debug]          xValue                   : " + xValue)
            console.debug("[debug]          yValue                   : " + yValue)
            console.debug("[debug]          yLogValue                : " + yLogValue)
            console.debug("[debug]          xPosition                : " + xPosition)
            console.debug("[debug]          yPosition                : " + yPosition)

            if(xPosition <= 0)
            {
                ctx.moveTo(xPosition,yPosition);
                continue;
            }

            ctx.lineTo(xPosition,yPosition);
            ctx.moveTo(xPosition,yPosition);

            canvas.lastPaintIdx = i;

            if(xValue > startX + xRange)
                break;
        }

        ctx.stroke();

        canvas.requestPaint();
    }

    onLineColorChanged : { clear() }

    onLineWidthChanged : { clear() }

    onLogBaseChanged     : { clear() }

    onLogStartExpChanged : { clear() }

    onLogEndExpChanged   : { clear() }

    onXRangeChanged    : { clear() }

    onStartXChanged    : { clear() }
}
