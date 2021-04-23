import QtQuick.Window 2.12
import QtQuick 2.12
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.5
import QtQuick.Controls.Styles 1.4
import QtGraphicalEffects 1.0
import "./"
import "./image/"
import QmlEnumDef 1.0
import FontManager 1.0

UiDialog {
    id: dialog

    property var isShift : false
    property var labelText : ""
    property var parentTextControl : null

    contentHeight: 530; contentWidth: 1010
    anchors.centerIn : Overlay.overlay
    bgSource : "/control/image/panel-bg-keypad-dialog.png"

    Component.onCompleted: {
        dialog.labelText = dialog.parentTextControl.labelText
        inputField.text = ""+dialog.parentTextControl.text
        inputField.forceActiveFocus();
        inputField.selectAll()
        inputField.cursorVisible = true
    }

    onVisibleChanged:
    {
        if(dialog.visible)
            return;

        dialog.destroy();
    }

    function inputKey(keyValue)
    {
        var cursorIdx = inputField.selectionStart

        if(inputField.selectionStart === inputField.selectionEnd)
        {
            inputField.text = inputField.text.substr(0,inputField.selectionStart) + keyValue + inputField.text.substring(inputField.selectionEnd, inputField.text.length)
        }
        else
        {
            inputField.text = inputField.text.substr(0,inputField.selectionStart) + keyValue + inputField.text.substring(inputField.selectionEnd + 1, inputField.text.length)
        }

        inputField.moveCursorSelection(cursorIdx + 1)
        inputField.select(cursorIdx + 1,cursorIdx + 1)
    }

    function inputDel()
    {
        var cursorIdx = inputField.selectionStart

        if(inputField.selectionStart === inputField.selectionEnd)
        {
            if(inputField.selectionStart == 0)
                return;

            inputField.text = inputField.text.substr(0,inputField.selectionStart - 1) + inputField.text.substring(inputField.selectionEnd, inputField.text.length)
            inputField.moveCursorSelection(cursorIdx - 1)
            inputField.select(cursorIdx - 1,cursorIdx - 1)
        }
        else
        {
            inputField.text = inputField.text.substr(0,inputField.selectionStart) + inputField.text.substring(inputField.selectionEnd + 1, inputField.text.length)
            inputField.moveCursorSelection(cursorIdx)
            inputField.select(cursorIdx, cursorIdx)
        }
    }

    contentItem: Item{
        Item{
            id : titleBox
            height: 80; width: parent.width
            anchors.top: parent.top; anchors.horizontalCenter: parent.horizontalCenter

            UiText{
                anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.left; anchors.leftMargin : 20

                text: dialog.labelText
            }

            UiButton{
                height: 52; width: 52
                anchors.verticalCenter: parent.verticalCenter; anchors.right: parent.right; anchors.rightMargin: 20

                norImage: "/control/image/close-btn-bg.png"
                pressImage: "/control/image/close-btn-press-bg.png"

                onClicked: {
                    dialog.close();
                }
            }
        }

        TextField{
            id : inputField
            height: 80; z : 1

            anchors.top: titleBox.bottom; anchors.topMargin : 20; anchors.left: parent.left; anchors.leftMargin: 30; anchors.right: parent.right; anchors.rightMargin: 30
            background: Rectangle{ color: "#59000000"; radius: 5; border.width: 0}

            color: "#FFFFFF"
            font.family: FontManager.nanumGothicName; font.pixelSize: 30
        }

        ColumnLayout{
            anchors.top: inputField.bottom; anchors.topMargin : 20; anchors.bottom: parent.bottom; anchors.bottomMargin: 20; anchors.left: parent.left; anchors.leftMargin: 30; anchors.right: parent.right; anchors.rightMargin: 30
            spacing: 10;

            RowLayout{
                Layout.preferredHeight: 1; Layout.preferredWidth: 1; Layout.fillHeight: true; Layout.fillWidth: true
                spacing: 10;

                UiButton{
                    Layout.fillHeight: true; Layout.fillWidth: true
                    Layout.preferredHeight: 1; Layout.preferredWidth: 70;
                    norImage: "image/n-s-circle-btn-bg.png"; pressImage: "image/n-s-circle-btn-press-bg.png"
                    text: "1"
                    focusPolicy: Qt.NoFocus

                    onClicked: {
                        dialog.inputKey(text)
                    }
                }

                UiButton{
                    Layout.fillHeight: true; Layout.fillWidth: true
                    Layout.preferredHeight: 1; Layout.preferredWidth: 70;
                    norImage: "image/n-s-circle-btn-bg.png"; pressImage: "image/n-s-circle-btn-press-bg.png"
                    text: "2"
                    focusPolicy: Qt.NoFocus

                    onClicked: {
                        dialog.inputKey(text)
                    }
                }

                UiButton{
                    Layout.fillHeight: true; Layout.fillWidth: true
                    Layout.preferredHeight: 1; Layout.preferredWidth: 70;
                    norImage: "image/n-s-circle-btn-bg.png"; pressImage: "image/n-s-circle-btn-press-bg.png"
                    text: "3"
                    focusPolicy: Qt.NoFocus

                    onClicked: {
                        dialog.inputKey(text)
                    }
                }

                UiButton{
                    Layout.fillHeight: true; Layout.fillWidth: true
                    Layout.preferredHeight: 1; Layout.preferredWidth: 70;
                    norImage: "image/n-s-circle-btn-bg.png"; pressImage: "image/n-s-circle-btn-press-bg.png"
                    text: "4"
                    focusPolicy: Qt.NoFocus

                    onClicked: {
                        dialog.inputKey(text)
                    }
                }

                UiButton{
                    Layout.fillHeight: true; Layout.fillWidth: true
                    Layout.preferredHeight: 1; Layout.preferredWidth: 70;
                    norImage: "image/n-s-circle-btn-bg.png"; pressImage: "image/n-s-circle-btn-press-bg.png"
                    text: "5"
                    focusPolicy: Qt.NoFocus

                    onClicked: {
                        dialog.inputKey(text)
                    }
                }

                UiButton{
                    Layout.fillHeight: true; Layout.fillWidth: true
                    Layout.preferredHeight: 1; Layout.preferredWidth: 70;
                    norImage: "image/n-s-circle-btn-bg.png"; pressImage: "image/n-s-circle-btn-press-bg.png"
                    text: "6"
                    focusPolicy: Qt.NoFocus

                    onClicked: {
                        dialog.inputKey(text)
                    }
                }

                UiButton{
                    Layout.fillHeight: true; Layout.fillWidth: true
                    Layout.preferredHeight: 1; Layout.preferredWidth: 70;
                    norImage: "image/n-s-circle-btn-bg.png"; pressImage: "image/n-s-circle-btn-press-bg.png"
                    text: "7"
                    focusPolicy: Qt.NoFocus

                    onClicked: {
                        dialog.inputKey(text)
                    }
                }

                UiButton{
                    Layout.fillHeight: true; Layout.fillWidth: true
                    Layout.preferredHeight: 1; Layout.preferredWidth: 70;
                    norImage: "image/n-s-circle-btn-bg.png"; pressImage: "image/n-s-circle-btn-press-bg.png"
                    text: "8"
                    focusPolicy: Qt.NoFocus

                    onClicked: {
                        dialog.inputKey(text)
                    }
                }

                UiButton{
                    Layout.fillHeight: true; Layout.fillWidth: true
                    Layout.preferredHeight: 1; Layout.preferredWidth: 70;
                    norImage: "image/n-s-circle-btn-bg.png"; pressImage: "image/n-s-circle-btn-press-bg.png"
                    text: "9"
                    focusPolicy: Qt.NoFocus

                    onClicked: {
                        dialog.inputKey(text)
                    }
                }

                UiButton{
                    Layout.fillHeight: true; Layout.fillWidth: true
                    Layout.preferredHeight: 1; Layout.preferredWidth: 70;
                    norImage: "image/n-s-circle-btn-bg.png"; pressImage: "image/n-s-circle-btn-press-bg.png"
                    text: "0"
                    focusPolicy: Qt.NoFocus

                    onClicked: {
                        dialog.inputKey(text)
                    }
                }

                UiButton{
                    Layout.fillHeight: true; Layout.fillWidth: true
                    Layout.preferredHeight: 1; Layout.preferredWidth: 70;
                    norImage: "image/n-s-circle-btn-bg.png"; pressImage: "image/n-s-circle-btn-press-bg.png"
                    text: "-"
                    focusPolicy: Qt.NoFocus

                    onClicked: {
                        dialog.inputKey(text)
                    }
                }

                UiButton{
                    Layout.fillHeight: true; Layout.fillWidth: true
                    Layout.preferredHeight: 1; Layout.preferredWidth: 70;
                    norImage: "image/n-s-circle-btn-bg.png"; pressImage: "image/n-s-circle-btn-press-bg.png"
                    text: "+"
                    focusPolicy: Qt.NoFocus

                    onClicked: {
                        dialog.inputKey(text)
                    }
                }
            }

            RowLayout{
                Layout.preferredHeight: 1; Layout.preferredWidth: 1; Layout.fillHeight: true; Layout.fillWidth: true
                spacing: 10;

                Item{
                    Layout.fillHeight: true; Layout.fillWidth: true
                    Layout.preferredHeight: 1; Layout.preferredWidth: 25;
                }

                UiButton{
                    Layout.fillHeight: true; Layout.fillWidth: true
                    Layout.preferredHeight: 1; Layout.preferredWidth: 70;
                    norImage: "image/n-s-circle-btn-bg.png"; pressImage: "image/n-s-circle-btn-press-bg.png"
                    text: dialog.isShift ? "q" : "Q"
                    focusPolicy: Qt.NoFocus

                    onClicked: {
                        dialog.inputKey(text)
                    }
                }

                UiButton{
                    Layout.fillHeight: true; Layout.fillWidth: true
                    Layout.preferredHeight: 1; Layout.preferredWidth: 70;
                    norImage: "image/n-s-circle-btn-bg.png"; pressImage: "image/n-s-circle-btn-press-bg.png"
                    text: dialog.isShift ? "w" : "W"
                    focusPolicy: Qt.NoFocus

                    onClicked: {
                        dialog.inputKey(text)
                    }
                }

                UiButton{
                    Layout.fillHeight: true; Layout.fillWidth: true
                    Layout.preferredHeight: 1; Layout.preferredWidth: 70;
                    norImage: "image/n-s-circle-btn-bg.png"; pressImage: "image/n-s-circle-btn-press-bg.png"
                    text: dialog.isShift ? "e" : "E"
                    focusPolicy: Qt.NoFocus

                    onClicked: {
                        dialog.inputKey(text)
                    }
                }

                UiButton{
                    Layout.fillHeight: true; Layout.fillWidth: true
                    Layout.preferredHeight: 1; Layout.preferredWidth: 70;
                    norImage: "image/n-s-circle-btn-bg.png"; pressImage: "image/n-s-circle-btn-press-bg.png"
                    text: dialog.isShift ? "r" : "R"
                    focusPolicy: Qt.NoFocus

                    onClicked: {
                        dialog.inputKey(text)
                    }
                }

                UiButton{
                    Layout.fillHeight: true; Layout.fillWidth: true
                    Layout.preferredHeight: 1; Layout.preferredWidth: 70;
                    norImage: "image/n-s-circle-btn-bg.png"; pressImage: "image/n-s-circle-btn-press-bg.png"
                    text: dialog.isShift ? "t" : "T"
                    focusPolicy: Qt.NoFocus

                    onClicked: {
                        dialog.inputKey(text)
                    }
                }

                UiButton{
                    Layout.fillHeight: true; Layout.fillWidth: true
                    Layout.preferredHeight: 1; Layout.preferredWidth: 70;
                    norImage: "image/n-s-circle-btn-bg.png"; pressImage: "image/n-s-circle-btn-press-bg.png"
                    text: dialog.isShift ? "y" : "Y"
                    focusPolicy: Qt.NoFocus

                    onClicked: {
                        dialog.inputKey(text)
                    }
                }

                UiButton{
                    Layout.fillHeight: true; Layout.fillWidth: true
                    Layout.preferredHeight: 1; Layout.preferredWidth: 70;
                    norImage: "image/n-s-circle-btn-bg.png"; pressImage: "image/n-s-circle-btn-press-bg.png"
                    text: dialog.isShift ? "u" : "U"
                    focusPolicy: Qt.NoFocus

                    onClicked: {
                        dialog.inputKey(text)
                    }
                }

                UiButton{
                    Layout.fillHeight: true; Layout.fillWidth: true
                    Layout.preferredHeight: 1; Layout.preferredWidth: 70;
                    norImage: "image/n-s-circle-btn-bg.png"; pressImage: "image/n-s-circle-btn-press-bg.png"
                    text: dialog.isShift ? "i" : "I"
                    focusPolicy: Qt.NoFocus

                    onClicked: {
                        dialog.inputKey(text)
                    }
                }

                UiButton{
                    Layout.fillHeight: true; Layout.fillWidth: true
                    Layout.preferredHeight: 1; Layout.preferredWidth: 70;
                    norImage: "image/n-s-circle-btn-bg.png"; pressImage: "image/n-s-circle-btn-press-bg.png"
                    text: dialog.isShift ? "o" : "O"
                    focusPolicy: Qt.NoFocus

                    onClicked: {
                        dialog.inputKey(text)
                    }
                }

                UiButton{
                    Layout.fillHeight: true; Layout.fillWidth: true
                    Layout.preferredHeight: 1; Layout.preferredWidth: 70;
                    norImage: "image/n-s-circle-btn-bg.png"; pressImage: "image/n-s-circle-btn-press-bg.png"
                    text: dialog.isShift ? "p" : "P"
                    focusPolicy: Qt.NoFocus

                    onClicked: {
                        dialog.inputKey(text)
                    }
                }
                UiButton{
                    Layout.fillHeight: true; Layout.fillWidth: true
                    Layout.preferredHeight: 1; Layout.preferredWidth: 105
                    norImage: "image/n-s-circle-btn-bg.png"; pressImage: "image/n-s-circle-btn-press-bg.png"
                    text: "←"
                    focusPolicy: Qt.NoFocus

                    onClicked: {
                        dialog.inputDel()
                    }
                }
            }

            RowLayout{
                Layout.preferredHeight: 1; Layout.preferredWidth: 1; Layout.fillHeight: true; Layout.fillWidth: true
                spacing: 10;

                UiButton{
                    Layout.fillHeight: true; Layout.fillWidth: true
                    Layout.preferredHeight: 1; Layout.preferredWidth: 70;
                    norImage: "image/n-s-circle-btn-bg.png"; pressImage: "image/n-s-circle-btn-press-bg.png"
                    text: ""
                    focusPolicy: Qt.NoFocus

                    enabled: false
                }

                UiButton{
                    Layout.fillHeight: true; Layout.fillWidth: true
                    Layout.preferredHeight: 1; Layout.preferredWidth: 70;
                    norImage: "image/n-s-circle-btn-bg.png"; pressImage: "image/n-s-circle-btn-press-bg.png"
                    text: dialog.isShift ? "a" : "A"
                    focusPolicy: Qt.NoFocus

                    onClicked: {
                        dialog.inputKey(text)
                    }
                }

                UiButton{
                    Layout.fillHeight: true; Layout.fillWidth: true
                    Layout.preferredHeight: 1; Layout.preferredWidth: 70;
                    norImage: "image/n-s-circle-btn-bg.png"; pressImage: "image/n-s-circle-btn-press-bg.png"
                    text: dialog.isShift ? "s" : "S"
                    focusPolicy: Qt.NoFocus

                    onClicked: {
                        dialog.inputKey(text)
                    }
                }

                UiButton{
                    Layout.fillHeight: true; Layout.fillWidth: true
                    Layout.preferredHeight: 1; Layout.preferredWidth: 70;
                    norImage: "image/n-s-circle-btn-bg.png"; pressImage: "image/n-s-circle-btn-press-bg.png"
                    text: dialog.isShift ? "d" : "D"
                    focusPolicy: Qt.NoFocus

                    onClicked: {
                        dialog.inputKey(text)
                    }
                }

                UiButton{
                    Layout.fillHeight: true; Layout.fillWidth: true
                    Layout.preferredHeight: 1; Layout.preferredWidth: 70;
                    norImage: "image/n-s-circle-btn-bg.png"; pressImage: "image/n-s-circle-btn-press-bg.png"
                    text: dialog.isShift ? "f" : "F"
                    focusPolicy: Qt.NoFocus

                    onClicked: {
                        dialog.inputKey(text)
                    }
                }

                UiButton{
                    Layout.fillHeight: true; Layout.fillWidth: true
                    Layout.preferredHeight: 1; Layout.preferredWidth: 70;
                    norImage: "image/n-s-circle-btn-bg.png"; pressImage: "image/n-s-circle-btn-press-bg.png"
                    text: dialog.isShift ? "g" : "G"
                    focusPolicy: Qt.NoFocus

                    onClicked: {
                        dialog.inputKey(text)
                    }
                }

                UiButton{
                    Layout.fillHeight: true; Layout.fillWidth: true
                    Layout.preferredHeight: 1; Layout.preferredWidth: 70;
                    norImage: "image/n-s-circle-btn-bg.png"; pressImage: "image/n-s-circle-btn-press-bg.png"
                    text: dialog.isShift ? "h" : "H"
                    focusPolicy: Qt.NoFocus

                    onClicked: {
                        dialog.inputKey(text)
                    }
                }

                UiButton{
                    Layout.fillHeight: true; Layout.fillWidth: true
                    Layout.preferredHeight: 1; Layout.preferredWidth: 70;
                    norImage: "image/n-s-circle-btn-bg.png"; pressImage: "image/n-s-circle-btn-press-bg.png"
                    text: dialog.isShift ? "j" : "J"
                    focusPolicy: Qt.NoFocus

                    onClicked: {
                        dialog.inputKey(text)
                    }
                }

                UiButton{
                    Layout.fillHeight: true; Layout.fillWidth: true
                    Layout.preferredHeight: 1; Layout.preferredWidth: 70;
                    norImage: "image/n-s-circle-btn-bg.png"; pressImage: "image/n-s-circle-btn-press-bg.png"
                    text: dialog.isShift ? "k" : "K"
                    focusPolicy: Qt.NoFocus

                    onClicked: {
                        dialog.inputKey(text)
                    }
                }

                UiButton{
                    Layout.fillHeight: true; Layout.fillWidth: true
                    Layout.preferredHeight: 1; Layout.preferredWidth: 70;
                    norImage: "image/n-s-circle-btn-bg.png"; pressImage: "image/n-s-circle-btn-press-bg.png"
                    text: dialog.isShift ? "l" : "L"
                    focusPolicy: Qt.NoFocus

                    onClicked: {
                        dialog.inputKey(text)
                    }
                }

                UiButton{
                    Layout.fillHeight: true; Layout.fillWidth: true
                    Layout.preferredHeight: 1; Layout.preferredWidth: 150;
                    norImage: "image/n-s-circle-btn-bg.png"; pressImage: "image/n-s-circle-btn-press-bg.png"
                    text: "↵"
                    focusPolicy: Qt.NoFocus

                    onClicked: {
                        parentTextControl.onResultKeypad(inputField.text)
                        dialog.close()
                    }
                }
            }

            RowLayout{
                Layout.preferredHeight: 1; Layout.preferredWidth: 1; Layout.fillHeight: true; Layout.fillWidth: true
                spacing: 10;

                UiButton{
                    Layout.fillHeight: true; Layout.fillWidth: true
                    Layout.preferredHeight: 1; Layout.preferredWidth: 70;
                    norImage: "image/n-s-circle-btn-bg.png"; pressImage: "image/n-s-circle-btn-press-bg.png"
                    text: ""
                    focusPolicy: Qt.NoFocus
                    enabled: false
                }

                UiButton{
                    Layout.fillHeight: true; Layout.fillWidth: true
                    Layout.preferredHeight: 1; Layout.preferredWidth: 70;
                    norImage: "image/n-s-circle-btn-bg.png"; pressImage: "image/n-s-circle-btn-press-bg.png"
                    text: ""
                    focusPolicy: Qt.NoFocus
                    enabled: false
                }

                UiButton{
                    Layout.fillHeight: true; Layout.fillWidth: true
                    Layout.preferredHeight: 1; Layout.preferredWidth: 70;
                    norImage: "image/n-s-circle-btn-bg.png"; pressImage: "image/n-s-circle-btn-press-bg.png"
                    text: dialog.isShift ? "z" : "Z"
                    focusPolicy: Qt.NoFocus

                    onClicked: {
                        dialog.inputKey(text)
                    }
                }

                UiButton{
                    Layout.fillHeight: true; Layout.fillWidth: true
                    Layout.preferredHeight: 1; Layout.preferredWidth: 70;
                    norImage: "image/n-s-circle-btn-bg.png"; pressImage: "image/n-s-circle-btn-press-bg.png"
                    text: dialog.isShift ? "x" : "X"
                    focusPolicy: Qt.NoFocus

                    onClicked: {
                        dialog.inputKey(text)
                    }
                }

                UiButton{
                    Layout.fillHeight: true; Layout.fillWidth: true
                    Layout.preferredHeight: 1; Layout.preferredWidth: 70;
                    norImage: "image/n-s-circle-btn-bg.png"; pressImage: "image/n-s-circle-btn-press-bg.png"
                    text: dialog.isShift ? "c" : "C"
                    focusPolicy: Qt.NoFocus

                    onClicked: {
                        dialog.inputKey(text)
                    }
                }

                UiButton{
                    Layout.fillHeight: true; Layout.fillWidth: true
                    Layout.preferredHeight: 1; Layout.preferredWidth: 70;
                    norImage: "image/n-s-circle-btn-bg.png"; pressImage: "image/n-s-circle-btn-press-bg.png"
                    text: dialog.isShift ? "v" : "V"
                    focusPolicy: Qt.NoFocus

                    onClicked: {
                        dialog.inputKey(text)
                    }
                }

                UiButton{
                    Layout.fillHeight: true; Layout.fillWidth: true
                    Layout.preferredHeight: 1; Layout.preferredWidth: 70;
                    norImage: "image/n-s-circle-btn-bg.png"; pressImage: "image/n-s-circle-btn-press-bg.png"
                    text: dialog.isShift ? "b" : "B"
                    focusPolicy: Qt.NoFocus

                    onClicked: {
                        dialog.inputKey(text)
                    }
                }

                UiButton{
                    Layout.fillHeight: true; Layout.fillWidth: true
                    Layout.preferredHeight: 1; Layout.preferredWidth: 70;
                    norImage: "image/n-s-circle-btn-bg.png"; pressImage: "image/n-s-circle-btn-press-bg.png"
                    text: dialog.isShift ? "n" : "N"
                    focusPolicy: Qt.NoFocus

                    onClicked: {
                        dialog.inputKey(text)
                    }
                }

                UiButton{
                    Layout.fillHeight: true; Layout.fillWidth: true
                    Layout.preferredHeight: 1; Layout.preferredWidth: 70;
                    norImage: "image/n-s-circle-btn-bg.png"; pressImage: "image/n-s-circle-btn-press-bg.png"
                    text: dialog.isShift ? "m" : "M"
                    focusPolicy: Qt.NoFocus

                    onClicked: {
                        dialog.inputKey(text)
                    }
                }

                UiButton{
                    Layout.fillHeight: true; Layout.fillWidth: true
                    Layout.preferredHeight: 1; Layout.preferredWidth: 70;
                    norImage: "image/n-s-circle-btn-bg.png"; pressImage: "image/n-s-circle-btn-press-bg.png"
                    text: "‿"
                    focusPolicy: Qt.NoFocus

                    onClicked: {
                        dialog.inputKey(" ")
                    }
                }

                UiButton{
                    Layout.fillHeight: true; Layout.fillWidth: true
                    Layout.preferredHeight: 1; Layout.preferredWidth: 150;
                    norImage: "image/n-s-circle-btn-bg.png"; pressImage: "image/n-s-circle-btn-press-bg.png"
                    text: "SHIFT"
                    focusPolicy: Qt.NoFocus

                    onClicked: {
                        dialog.isShift = !dialog.isShift
                    }
                }
            }
        }

    }
}
