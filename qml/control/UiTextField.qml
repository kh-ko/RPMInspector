import "../ui/image/."

import QtQuick 2.12
import QtQuick.Controls 2.5
import QmlEnumDef 1.0
import EnumDef 1.0
import FontManager 1.0

Text {
    id : control

    property var  inputType : QmlEnumDef.INT_MODE
    property var  labelText : ""

    color: "#3F464E"
    font.family: FontManager.nanumGothicBName; font.bold  : true; font.pixelSize: 30

    signal signalChangedValue(string value)

    function onResultKeypad(value)
    {
        control.signalChangedValue(value)

        text = value
    }

    Rectangle{
        id : underLine
        height: 2; width: parent.width
        anchors.top: parent.bottom; anchors.horizontalCenter: parent.horizontalCenter
        color : "#9EAEC2"
    }

    MouseArea{
        anchors.fill: parent

        onClicked:{
            var keypad

            if(control.inputType === QmlEnumDef.INT_MODE || control.inputType === QmlEnumDef.FLOAT_MODE)
            {
                keypad = numberKeypad.createObject(control, {"parentTextControl" : control, "type" : QmlEnumDef.NUMBER_KEYPAD_TYPE_INT})
            }
            else
            {
                keypad = textKeypad.createObject(control, {"parentTextControl" : control})
            }

            keypad.open()
        }
    }

    Component{ id : numberKeypad; UiNumberKeypad {}}
    Component{ id : textKeypad  ; UiTextKeypad {}}
}
