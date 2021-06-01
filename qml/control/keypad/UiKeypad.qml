import QtQuick.Window 2.12
import QtQuick 2.12
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.5
import QtQuick.Controls.Styles 1.4
import QtGraphicalEffects 1.0
import "../"
import "../image/"
import QmlEnumDef 1.0
import FontManager 1.0
import KeypadModel 1.0

UiDialog {
    id: dialog

    property var isHangle : false
    property var isShift : false
    property var labelText : ""
    property var parentTextControl : null

    contentHeight: 530; contentWidth: 1010
    anchors.centerIn : Overlay.overlay
    bgSource : "/control/image/panel-bg-keypad-dialog.png"

    Component.onCompleted: {
        dialog.labelText = dialog.parentTextControl.labelText
        keypadModel.onCommandSetText(dialog.parentTextControl.text)
        inputField.text = keypadModel.mDpText
        inputField.forceActiveFocus();
        inputField.select(keypadModel.mSelectStart, keypadModel.mSelectEnd)
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
        keypadModel.onCommandInputKey(inputField.selectionStart, inputField.selectionEnd, keyValue)
        inputField.text = keypadModel.mDpText
        inputField.moveCursorSelection(keypadModel.mSelectStart)
        inputField.select(keypadModel.mSelectStart, keypadModel.mSelectEnd)
        /*
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
        */

    }

    function inputDel()
    {
        keypadModel.onCommandDelKey(inputField.selectionStart, inputField.selectionEnd)
        inputField.text = keypadModel.mDpText
        inputField.moveCursorSelection(keypadModel.mSelectStart)
        inputField.select(keypadModel.mSelectStart, keypadModel.mSelectEnd)
        /*
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
        */
    }

    contentItem: Item{

        KeypadModel{
            id : keypadModel
        }

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
                    norImage: "/control/image/n-s-circle-btn-bg.png"; pressImage: "/control/image/n-s-circle-btn-press-bg.png"
                    text: "1"
                    focusPolicy: Qt.NoFocus

                    onClicked: {
                        dialog.inputKey(text)
                    }
                }

                UiButton{
                    Layout.fillHeight: true; Layout.fillWidth: true
                    Layout.preferredHeight: 1; Layout.preferredWidth: 70;
                    norImage: "/control/image/n-s-circle-btn-bg.png"; pressImage: "/control/image/n-s-circle-btn-press-bg.png"
                    text: "2"
                    focusPolicy: Qt.NoFocus

                    onClicked: {
                        dialog.inputKey(text)
                    }
                }

                UiButton{
                    Layout.fillHeight: true; Layout.fillWidth: true
                    Layout.preferredHeight: 1; Layout.preferredWidth: 70;
                    norImage: "/control/image/n-s-circle-btn-bg.png"; pressImage: "/control/image/n-s-circle-btn-press-bg.png"
                    text: "3"
                    focusPolicy: Qt.NoFocus

                    onClicked: {
                        dialog.inputKey(text)
                    }
                }

                UiButton{
                    Layout.fillHeight: true; Layout.fillWidth: true
                    Layout.preferredHeight: 1; Layout.preferredWidth: 70;
                    norImage: "/control/image/n-s-circle-btn-bg.png"; pressImage: "/control/image/n-s-circle-btn-press-bg.png"
                    text: "4"
                    focusPolicy: Qt.NoFocus

                    onClicked: {
                        dialog.inputKey(text)
                    }
                }

                UiButton{
                    Layout.fillHeight: true; Layout.fillWidth: true
                    Layout.preferredHeight: 1; Layout.preferredWidth: 70;
                    norImage: "/control/image/n-s-circle-btn-bg.png"; pressImage: "/control/image/n-s-circle-btn-press-bg.png"
                    text: "5"
                    focusPolicy: Qt.NoFocus

                    onClicked: {
                        dialog.inputKey(text)
                    }
                }

                UiButton{
                    Layout.fillHeight: true; Layout.fillWidth: true
                    Layout.preferredHeight: 1; Layout.preferredWidth: 70;
                    norImage: "/control/image/n-s-circle-btn-bg.png"; pressImage: "/control/image/n-s-circle-btn-press-bg.png"
                    text: "6"
                    focusPolicy: Qt.NoFocus

                    onClicked: {
                        dialog.inputKey(text)
                    }
                }

                UiButton{
                    Layout.fillHeight: true; Layout.fillWidth: true
                    Layout.preferredHeight: 1; Layout.preferredWidth: 70;
                    norImage: "/control/image/n-s-circle-btn-bg.png"; pressImage: "/control/image/n-s-circle-btn-press-bg.png"
                    text: "7"
                    focusPolicy: Qt.NoFocus

                    onClicked: {
                        dialog.inputKey(text)
                    }
                }

                UiButton{
                    Layout.fillHeight: true; Layout.fillWidth: true
                    Layout.preferredHeight: 1; Layout.preferredWidth: 70;
                    norImage: "/control/image/n-s-circle-btn-bg.png"; pressImage: "/control/image/n-s-circle-btn-press-bg.png"
                    text: "8"
                    focusPolicy: Qt.NoFocus

                    onClicked: {
                        dialog.inputKey(text)
                    }
                }

                UiButton{
                    Layout.fillHeight: true; Layout.fillWidth: true
                    Layout.preferredHeight: 1; Layout.preferredWidth: 70;
                    norImage: "/control/image/n-s-circle-btn-bg.png"; pressImage: "/control/image/n-s-circle-btn-press-bg.png"
                    text: "9"
                    focusPolicy: Qt.NoFocus

                    onClicked: {
                        dialog.inputKey(text)
                    }
                }

                UiButton{
                    Layout.fillHeight: true; Layout.fillWidth: true
                    Layout.preferredHeight: 1; Layout.preferredWidth: 70;
                    norImage: "/control/image/n-s-circle-btn-bg.png"; pressImage: "/control/image/n-s-circle-btn-press-bg.png"
                    text: "0"
                    focusPolicy: Qt.NoFocus

                    onClicked: {
                        dialog.inputKey(text)
                    }
                }

                UiButton{
                    Layout.fillHeight: true; Layout.fillWidth: true
                    Layout.preferredHeight: 1; Layout.preferredWidth: 70;
                    norImage: "/control/image/n-s-circle-btn-bg.png"; pressImage: "/control/image/n-s-circle-btn-press-bg.png"
                    text: "-"
                    focusPolicy: Qt.NoFocus

                    onClicked: {
                        dialog.inputKey(text)
                    }
                }

                UiButton{
                    Layout.fillHeight: true; Layout.fillWidth: true
                    Layout.preferredHeight: 1; Layout.preferredWidth: 70;
                    norImage: "/control/image/n-s-circle-btn-bg.png"; pressImage: "/control/image/n-s-circle-btn-press-bg.png"
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
                    norImage: "/control/image/n-s-circle-btn-bg.png"; pressImage: "/control/image/n-s-circle-btn-press-bg.png"
                    text: dialog.isHangle && dialog.isShift ? "ㅃ" :
                          dialog.isHangle && !dialog.isShift ? "ㅂ":
                          !dialog.isHangle && dialog.isShift ? "Q" : "q"
                    focusPolicy: Qt.NoFocus

                    onClicked: {
                        dialog.inputKey(text)
                    }
                }

                UiButton{
                    Layout.fillHeight: true; Layout.fillWidth: true
                    Layout.preferredHeight: 1; Layout.preferredWidth: 70;
                    norImage: "/control/image/n-s-circle-btn-bg.png"; pressImage: "/control/image/n-s-circle-btn-press-bg.png"
                    text: dialog.isHangle && dialog.isShift ? "ㅉ" :
                          dialog.isHangle && !dialog.isShift ? "ㅈ":
                          !dialog.isHangle && dialog.isShift ? "W" : "w"
                    focusPolicy: Qt.NoFocus

                    onClicked: {
                        dialog.inputKey(text)
                    }
                }

                UiButton{
                    Layout.fillHeight: true; Layout.fillWidth: true
                    Layout.preferredHeight: 1; Layout.preferredWidth: 70;
                    norImage: "/control/image/n-s-circle-btn-bg.png"; pressImage: "/control/image/n-s-circle-btn-press-bg.png"
                    text: dialog.isHangle && dialog.isShift ? "ㄸ" :
                          dialog.isHangle && !dialog.isShift ? "ㄷ":
                          !dialog.isHangle && dialog.isShift ? "E" : "e"
                    focusPolicy: Qt.NoFocus

                    onClicked: {
                        dialog.inputKey(text)
                    }
                }

                UiButton{
                    Layout.fillHeight: true; Layout.fillWidth: true
                    Layout.preferredHeight: 1; Layout.preferredWidth: 70;
                    norImage: "/control/image/n-s-circle-btn-bg.png"; pressImage: "/control/image/n-s-circle-btn-press-bg.png"
                    text:  dialog.isHangle && dialog.isShift ? "ㄲ" :
                           dialog.isHangle && !dialog.isShift ? "ㄱ":
                           !dialog.isHangle && dialog.isShift ? "R" : "r"
                    focusPolicy: Qt.NoFocus

                    onClicked: {
                        dialog.inputKey(text)
                    }
                }

                UiButton{
                    Layout.fillHeight: true; Layout.fillWidth: true
                    Layout.preferredHeight: 1; Layout.preferredWidth: 70;
                    norImage: "/control/image/n-s-circle-btn-bg.png"; pressImage: "/control/image/n-s-circle-btn-press-bg.png"
                    text: dialog.isHangle && dialog.isShift ? "ㅆ" :
                          dialog.isHangle && !dialog.isShift ? "ㅅ":
                          !dialog.isHangle && dialog.isShift ? "T" : "t"
                    focusPolicy: Qt.NoFocus

                    onClicked: {
                        dialog.inputKey(text)
                    }
                }

                UiButton{
                    Layout.fillHeight: true; Layout.fillWidth: true
                    Layout.preferredHeight: 1; Layout.preferredWidth: 70;
                    norImage: "/control/image/n-s-circle-btn-bg.png"; pressImage: "/control/image/n-s-circle-btn-press-bg.png"
                    text: dialog.isHangle ? "ㅛ" :
                          !dialog.isHangle && dialog.isShift ? "Y" : "y"
                    focusPolicy: Qt.NoFocus

                    onClicked: {
                        dialog.inputKey(text)
                    }
                }

                UiButton{
                    Layout.fillHeight: true; Layout.fillWidth: true
                    Layout.preferredHeight: 1; Layout.preferredWidth: 70;
                    norImage: "/control/image/n-s-circle-btn-bg.png"; pressImage: "/control/image/n-s-circle-btn-press-bg.png"
                    text: dialog.isHangle ? "ㅕ" :
                          !dialog.isHangle && dialog.isShift ? "U" : "u"
                    focusPolicy: Qt.NoFocus

                    onClicked: {
                        dialog.inputKey(text)
                    }
                }

                UiButton{
                    Layout.fillHeight: true; Layout.fillWidth: true
                    Layout.preferredHeight: 1; Layout.preferredWidth: 70;
                    norImage: "/control/image/n-s-circle-btn-bg.png"; pressImage: "/control/image/n-s-circle-btn-press-bg.png"
                    text: dialog.isHangle ? "ㅑ" :
                          !dialog.isHangle && dialog.isShift ? "I" : "i"
                    focusPolicy: Qt.NoFocus

                    onClicked: {
                        dialog.inputKey(text)
                    }
                }

                UiButton{
                    Layout.fillHeight: true; Layout.fillWidth: true
                    Layout.preferredHeight: 1; Layout.preferredWidth: 70;
                    norImage: "/control/image/n-s-circle-btn-bg.png"; pressImage: "/control/image/n-s-circle-btn-press-bg.png"
                    text: dialog.isHangle && dialog.isShift ? "ㅒ" :
                          dialog.isHangle && !dialog.isShift ? "ㅐ":
                          !dialog.isHangle && dialog.isShift ? "O" : "o"
                    focusPolicy: Qt.NoFocus

                    onClicked: {
                        dialog.inputKey(text)
                    }
                }

                UiButton{
                    Layout.fillHeight: true; Layout.fillWidth: true
                    Layout.preferredHeight: 1; Layout.preferredWidth: 70;
                    norImage: "/control/image/n-s-circle-btn-bg.png"; pressImage: "/control/image/n-s-circle-btn-press-bg.png"
                    text: dialog.isHangle && dialog.isShift ? "ㅖ" :
                          dialog.isHangle && !dialog.isShift ? "ㅔ":
                          !dialog.isHangle && dialog.isShift ? "P" : "p"
                    focusPolicy: Qt.NoFocus

                    onClicked: {
                        dialog.inputKey(text)
                    }
                }
                UiButton{
                    Layout.fillHeight: true; Layout.fillWidth: true
                    Layout.preferredHeight: 1; Layout.preferredWidth: 105
                    norImage: "/control/image/n-s-circle-btn-bg.png"; pressImage: "/control/image/n-s-circle-btn-press-bg.png"
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
                    norImage: "/control/image/n-s-circle-btn-bg.png"; pressImage: "/control/image/n-s-circle-btn-press-bg.png"
                    text: ""
                    focusPolicy: Qt.NoFocus

                    enabled: false
                }

                UiButton{
                    Layout.fillHeight: true; Layout.fillWidth: true
                    Layout.preferredHeight: 1; Layout.preferredWidth: 70;
                    norImage: "/control/image/n-s-circle-btn-bg.png"; pressImage: "/control/image/n-s-circle-btn-press-bg.png"
                    text: dialog.isHangle ? "ㅁ" :
                          !dialog.isHangle && dialog.isShift ? "A" : "a"
                    focusPolicy: Qt.NoFocus

                    onClicked: {
                        dialog.inputKey(text)
                    }
                }

                UiButton{
                    Layout.fillHeight: true; Layout.fillWidth: true
                    Layout.preferredHeight: 1; Layout.preferredWidth: 70;
                    norImage: "/control/image/n-s-circle-btn-bg.png"; pressImage: "/control/image/n-s-circle-btn-press-bg.png"
                    text: dialog.isHangle ? "ㄴ" :
                          !dialog.isHangle && dialog.isShift ? "S" : "s"
                    focusPolicy: Qt.NoFocus

                    onClicked: {
                        dialog.inputKey(text)
                    }
                }

                UiButton{
                    Layout.fillHeight: true; Layout.fillWidth: true
                    Layout.preferredHeight: 1; Layout.preferredWidth: 70;
                    norImage: "/control/image/n-s-circle-btn-bg.png"; pressImage: "/control/image/n-s-circle-btn-press-bg.png"
                    text: dialog.isHangle ? "ㅇ" :
                          !dialog.isHangle && dialog.isShift ? "D" : "d"
                    focusPolicy: Qt.NoFocus

                    onClicked: {
                        dialog.inputKey(text)
                    }
                }

                UiButton{
                    Layout.fillHeight: true; Layout.fillWidth: true
                    Layout.preferredHeight: 1; Layout.preferredWidth: 70;
                    norImage: "/control/image/n-s-circle-btn-bg.png"; pressImage: "/control/image/n-s-circle-btn-press-bg.png"
                    text: dialog.isHangle ? "ㄹ" :
                          !dialog.isHangle && dialog.isShift ? "F" : "f"
                    focusPolicy: Qt.NoFocus

                    onClicked: {
                        dialog.inputKey(text)
                    }
                }

                UiButton{
                    Layout.fillHeight: true; Layout.fillWidth: true
                    Layout.preferredHeight: 1; Layout.preferredWidth: 70;
                    norImage: "/control/image/n-s-circle-btn-bg.png"; pressImage: "/control/image/n-s-circle-btn-press-bg.png"
                    text: dialog.isHangle ? "ㅎ" :
                          !dialog.isHangle && dialog.isShift ? "G" : "g"
                    focusPolicy: Qt.NoFocus

                    onClicked: {
                        dialog.inputKey(text)
                    }
                }

                UiButton{
                    Layout.fillHeight: true; Layout.fillWidth: true
                    Layout.preferredHeight: 1; Layout.preferredWidth: 70;
                    norImage: "/control/image/n-s-circle-btn-bg.png"; pressImage: "/control/image/n-s-circle-btn-press-bg.png"
                    text: dialog.isHangle ? "ㅗ" :
                          !dialog.isHangle && dialog.isShift ? "H" : "h"
                    focusPolicy: Qt.NoFocus

                    onClicked: {
                        dialog.inputKey(text)
                    }
                }

                UiButton{
                    Layout.fillHeight: true; Layout.fillWidth: true
                    Layout.preferredHeight: 1; Layout.preferredWidth: 70;
                    norImage: "/control/image/n-s-circle-btn-bg.png"; pressImage: "/control/image/n-s-circle-btn-press-bg.png"
                    text: dialog.isHangle ? "ㅓ" :
                          !dialog.isHangle && dialog.isShift ? "J" : "j"
                    focusPolicy: Qt.NoFocus

                    onClicked: {
                        dialog.inputKey(text)
                    }
                }

                UiButton{
                    Layout.fillHeight: true; Layout.fillWidth: true
                    Layout.preferredHeight: 1; Layout.preferredWidth: 70;
                    norImage: "/control/image/n-s-circle-btn-bg.png"; pressImage: "/control/image/n-s-circle-btn-press-bg.png"
                    text: dialog.isHangle ? "ㅏ" :
                          !dialog.isHangle && dialog.isShift ? "K" : "k"
                    focusPolicy: Qt.NoFocus

                    onClicked: {
                        dialog.inputKey(text)
                    }
                }

                UiButton{
                    Layout.fillHeight: true; Layout.fillWidth: true
                    Layout.preferredHeight: 1; Layout.preferredWidth: 70;
                    norImage: "/control/image/n-s-circle-btn-bg.png"; pressImage: "/control/image/n-s-circle-btn-press-bg.png"
                    text: dialog.isHangle ? "ㅣ" :
                          !dialog.isHangle && dialog.isShift ? "L" : "l"
                    focusPolicy: Qt.NoFocus

                    onClicked: {
                        dialog.inputKey(text)
                    }
                }

                UiButton{
                    Layout.fillHeight: true; Layout.fillWidth: true
                    Layout.preferredHeight: 1; Layout.preferredWidth: 150;
                    norImage: "/control/image/n-s-circle-btn-bg.png"; pressImage: "/control/image/n-s-circle-btn-press-bg.png"
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
                    norImage: "/control/image/n-s-circle-btn-bg.png"; pressImage: "/control/image/n-s-circle-btn-press-bg.png"
                    text: dialog.isHangle ? "영" : "한"
                    focusPolicy: Qt.NoFocus
                    enabled: true

                    onClicked: {
                        dialog.isHangle = !dialog.isHangle;
                    }
                }

                UiButton{
                    Layout.fillHeight: true; Layout.fillWidth: true
                    Layout.preferredHeight: 1; Layout.preferredWidth: 70;
                    norImage: "/control/image/n-s-circle-btn-bg.png"; pressImage: "/control/image/n-s-circle-btn-press-bg.png"
                    text: ""
                    focusPolicy: Qt.NoFocus
                    enabled: false
                }

                UiButton{
                    Layout.fillHeight: true; Layout.fillWidth: true
                    Layout.preferredHeight: 1; Layout.preferredWidth: 70;
                    norImage: "/control/image/n-s-circle-btn-bg.png"; pressImage: "/control/image/n-s-circle-btn-press-bg.png"
                    text: dialog.isHangle ? "ㅋ" :
                          !dialog.isHangle && dialog.isShift ? "Z" : "z"
                    focusPolicy: Qt.NoFocus

                    onClicked: {
                        dialog.inputKey(text)
                    }
                }

                UiButton{
                    Layout.fillHeight: true; Layout.fillWidth: true
                    Layout.preferredHeight: 1; Layout.preferredWidth: 70;
                    norImage: "/control/image/n-s-circle-btn-bg.png"; pressImage: "/control/image/n-s-circle-btn-press-bg.png"
                    text: dialog.isHangle ? "ㅌ" :
                          !dialog.isHangle && dialog.isShift ? "X" : "x"
                    focusPolicy: Qt.NoFocus

                    onClicked: {
                        dialog.inputKey(text)
                    }
                }

                UiButton{
                    Layout.fillHeight: true; Layout.fillWidth: true
                    Layout.preferredHeight: 1; Layout.preferredWidth: 70;
                    norImage: "/control/image/n-s-circle-btn-bg.png"; pressImage: "/control/image/n-s-circle-btn-press-bg.png"
                    text: dialog.isHangle ? "ㅊ" :
                          !dialog.isHangle && dialog.isShift ? "C" : "c"
                    focusPolicy: Qt.NoFocus

                    onClicked: {
                        dialog.inputKey(text)
                    }
                }

                UiButton{
                    Layout.fillHeight: true; Layout.fillWidth: true
                    Layout.preferredHeight: 1; Layout.preferredWidth: 70;
                    norImage: "/control/image/n-s-circle-btn-bg.png"; pressImage: "/control/image/n-s-circle-btn-press-bg.png"
                    text: dialog.isHangle ? "ㅍ" :
                          !dialog.isHangle && dialog.isShift ? "V" : "v"
                    focusPolicy: Qt.NoFocus

                    onClicked: {
                        dialog.inputKey(text)
                    }
                }

                UiButton{
                    Layout.fillHeight: true; Layout.fillWidth: true
                    Layout.preferredHeight: 1; Layout.preferredWidth: 70;
                    norImage: "/control/image/n-s-circle-btn-bg.png"; pressImage: "/control/image/n-s-circle-btn-press-bg.png"
                    text: dialog.isHangle ? "ㅠ" :
                          !dialog.isHangle && dialog.isShift ? "B" : "b"
                    focusPolicy: Qt.NoFocus

                    onClicked: {
                        dialog.inputKey(text)
                    }
                }

                UiButton{
                    Layout.fillHeight: true; Layout.fillWidth: true
                    Layout.preferredHeight: 1; Layout.preferredWidth: 70;
                    norImage: "/control/image/n-s-circle-btn-bg.png"; pressImage: "/control/image/n-s-circle-btn-press-bg.png"
                    text: dialog.isHangle ? "ㅜ" :
                          !dialog.isHangle && dialog.isShift ? "N" : "n"
                    focusPolicy: Qt.NoFocus

                    onClicked: {
                        dialog.inputKey(text)
                    }
                }

                UiButton{
                    Layout.fillHeight: true; Layout.fillWidth: true
                    Layout.preferredHeight: 1; Layout.preferredWidth: 70;
                    norImage: "/control/image/n-s-circle-btn-bg.png"; pressImage: "/control/image/n-s-circle-btn-press-bg.png"
                    text: dialog.isHangle ? "ㅡ" :
                          !dialog.isHangle && dialog.isShift ? "M" : "m"
                    focusPolicy: Qt.NoFocus

                    onClicked: {
                        dialog.inputKey(text)
                    }
                }

                UiButton{
                    Layout.fillHeight: true; Layout.fillWidth: true
                    Layout.preferredHeight: 1; Layout.preferredWidth: 70;
                    norImage: "/control/image/n-s-circle-btn-bg.png"; pressImage: "/control/image/n-s-circle-btn-press-bg.png"
                    text: "‿"
                    focusPolicy: Qt.NoFocus

                    onClicked: {
                        dialog.inputKey(" ")
                    }
                }

                UiButton{
                    Layout.fillHeight: true; Layout.fillWidth: true
                    Layout.preferredHeight: 1; Layout.preferredWidth: 150;
                    norImage: "/control/image/n-s-circle-btn-bg.png"; pressImage: "/control/image/n-s-circle-btn-press-bg.png"
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
