import QtQuick 2.12
import FontManager 1.0

Item {
    id : control

    property var   logBase        : 10
    property var   logStartExp    : -3
    property var   logEndExp      : 3

    property var   yAxisItemMargin   : 10
    property var   yAxisLineWidth    : 2
    property var   yAxisLineColor    : "#4dFFFFFF"
    property var   yAxisItemColor    : "#9e9e9e"
    property var   yAxisItemFontSize : 20
    property var   yAxisItemHieght   : 30
    property var   yAxisItemWidth    : 100
    property var   isRightYAxis      : false
    property var   yAxisDivideCount  : logEndExp - logStartExp

    visible: logStartExp < logEndExp


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

        if(!(logStartExp < logEndExp))
            return;

        for(var i = 0; i <= control.yAxisDivideCount; i ++)
        {
            yLine.createObject(control, {"height" : control.yAxisItemHieght, "lineIdx" : i, "base" : control.logBase, "exp" : (logStartExp + i)})
        }

    }

    Component.onCompleted : { draw() }
    onLogBaseChanged      : { draw() }
    onLogStartExpChanged  : { draw() }
    onLogEndExpChanged    : { draw() }

    Component{
        id : yLine;

        Item{
            property var base
            property var exp
            property var lineIdx

            x : 0;
            anchors.verticalCenter: parent.bottom;
            anchors.verticalCenterOffset: -1 * ((control.height / control.yAxisDivideCount) * lineIdx);
            anchors.left:parent.left; anchors.leftMargin: 0; anchors.right: parent.right; anchors.rightMargin: 0

            Item{
                id : yAxisItem
                height: parent.height; width: control.yAxisItemWidth - control.yAxisItemMargin;
                anchors.right: control.isRightYAxis ? parent.right : undefined; anchors.rightMargin: control.isRightYAxis ? 0 : undefined;

                Text{
                    id : yAxisItemExp
                    height: parent.height / 2;
                    anchors.top: parent.top; anchors.topMargin: 0; anchors.right: parent.right; anchors.rightMargin: 0

                    verticalAlignment: Text.AlignBottom; horizontalAlignment: Text.AlignRight;
                    color : control.yAxisItemColor

                    font.family: FontManager.nanumGothicName; font.pixelSize: (control.yAxisItemFontSize / 2);
                    text : ""+exp
                }

                Text{
                    id : yAxisItemBase
                    height: parent.height;
                    anchors.top: parent.top; anchors.topMargin: 0; anchors.right: yAxisItemExp.left; anchors.rightMargin: 2

                    verticalAlignment: Text.AlignVCenter; horizontalAlignment: Text.AlignRight;
                    color : control.yAxisItemColor

                    font.family: FontManager.nanumGothicName; font.pixelSize: control.yAxisItemFontSize;
                    text : ""+base
                }
            }

            Rectangle{
                height:control.yAxisLineWidth
                anchors.verticalCenter: parent.verticalCenter;
                anchors.left:control.isRightYAxis ? parent.left : yAxisItem.right; anchors.leftMargin: control.isRightYAxis ? 0 :control.yAxisItemMargin;
                anchors.right: control.isRightYAxis ? yAxisItem.left : parent.right; anchors.rightMargin:  control.isRightYAxis ? control.yAxisItemMargin : 0

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
