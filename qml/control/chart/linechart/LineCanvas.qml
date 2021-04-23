import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import LineChartData 1.0

Canvas {
    id : canvas

    property var graphData     : null
    property var lineColor
    property var lineWidth
    property var yRange
    property var startY
    property var xRange
    property var startX

    property var lastPaintIdx

    renderTarget : Canvas.FramebufferObject

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

        canvas.lastPaintIdx = graphData.onCommandGetNearMinIdx(canvas.startX) - 1;
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

        for(var i = drawStartIdx; ; i ++)
        {
            if( i > canvas.graphData.mLastIdx)
                break;

            var xValue = canvas.graphData.onCommandGetXValue(i);
            var yValue = canvas.graphData.onCommandGetYValue(i);

            var xPosition = (canvas.width * ((xValue - canvas.startX) / canvas.xRange))
            var yPosition = canvas.height - (canvas.height * ((yValue - canvas.startY) / canvas.yRange))

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

    onYRangeChanged    : { clear() }

    onStartYChanged    : { clear() }

    onXRangeChanged    : { clear() }

    onStartXChanged    : { clear() }
}
