import QtQuick 2.12
import FontManager 1.0

Item {
    id : control

    property var   valueDivder    : 1
    property var   valueFixedN    : 0
    property var   valueRange     : 100
    property var   startValue     : 0

    property var   yAxisItemMargin   : 10
    property var   yAxisLineWidth    : 2
    property var   yAxisLineColor    : "#4dFFFFFF"
    property var   yAxisItemColor    : "#9e9e9e"
    property var   yAxisItemFontSize : 20
    property var   yAxisItemHieght   : 30
    property var   yAxisItemWidth    : 100
    property var   yAxisDivideCount  : 1

    property var   isCenterZero      : false

    visible: control.yAxisDivideCount > 1

    function clear()
    {
        for(var i = 0; i < control.children.length; i ++)
        {
            control.children[i].destroy();
        }
    }

    function draw()
    {
        clear();

        if(control.yAxisDivideCount < 2)
            return;

        if(control.isCenterZero && ((control.yAxisDivideCount %2 !== 0) || (-1 * startValue) !== (valueRange / 2)))
        {
            console.debug("[ChartYaxis] zero center, divider count = " + control.yAxisDivideCount + ", startValue = " + startValue + ", valueRange = " + valueRange)
            return;
        }

        var gab = (control.valueRange / control.yAxisDivideCount)
        gab = gab / control.valueDivder
        gab = gab * Math.pow(10, control.valueFixedN)
        gab = Math.ceil(gab)
        gab = gab / Math.pow(10, control.valueFixedN)
        gab = gab * control.valueDivder

        if(control.isCenterZero)
        {
            yLine.createObject(control, {"height" : control.yAxisItemHieght, "value" : 0})

            for(var i = 1; i < yAxisDivideCount / 2; i++)
            {
                yLine.createObject(control, {"height" : control.yAxisItemHieght, "value" : gab * i})
            }
            for(var j = 1; j < yAxisDivideCount / 2; j++)
            {
                yLine.createObject(control, {"height" : control.yAxisItemHieght, "value" : -1 * gab * j})
            }
        }
        else
        {
            for(var k = 0; k <= yAxisDivideCount; k ++)
            {
                yLine.createObject(control, {"height" : control.yAxisItemHieght, "value" : startValue + (gab * k)})
            }
        }

    }

    onYAxisDivideCountChanged: { draw() }
    onValueDivderChanged     : { draw() }
    onValueFixedNChanged     : { draw() }
    onValueRangeChanged      : { draw() }
    onStartValueChanged      : { draw() }


    Component{
        id : yLine;

        Item{
            property var value

            x : 0;
            anchors.verticalCenter: parent.bottom;
            anchors.verticalCenterOffset: -1 * (parent.height * ((value - startValue) /valueRange));
            anchors.left:parent.left; anchors.leftMargin: 0; anchors.right: parent.right; anchors.rightMargin: 0

            visible: (-1*anchors.verticalCenterOffset >= 0) && (-1*anchors.verticalCenterOffset <= parent.height)

            Component.onCompleted : {
                console.debug("offset : " + anchors.verticalCenterOffset)
            }

            Text{
                id : yAxisItem
                height: parent.height; width: control.yAxisItemWidth - control.yAxisItemMargin;

                verticalAlignment: Text.AlignVCenter; horizontalAlignment: Text.AlignRight;
                color : control.yAxisItemColor
                elide: Text.ElideRight

                font.family: FontManager.nanumGothicName; font.pixelSize: control.yAxisItemFontSize;
                text : (value/control.valueDivder).toLocaleString(FontManager.locale, 'f', control.valueFixedN)
            }

            Rectangle{
                height:control.yAxisLineWidth
                anchors.verticalCenter: parent.verticalCenter; anchors.left:yAxisItem.right; anchors.leftMargin: control.yAxisItemMargin; anchors.right: parent.right; anchors.rightMargin: 0

                color : control.yAxisLineColor
            }
        }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
