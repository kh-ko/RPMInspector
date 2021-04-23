import QtQuick.Window 2.12
import QtQuick 2.12
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.5
import QtQuick.Controls.Styles 1.4
import QtGraphicalEffects 1.0
import "./"
import QmlEnumDef 1.0
import FontManager 1.0

Item {
    height: 530; width: 1010
    Item {
        id : inputField
        y : 100;
        height: 80; width: 800;
        horizontalCenter: parent.horizontalCenter
    }


}

/*

            UiButton{
                Layout.fillHeight: true; Layout.fillWidth: true
                Layout.preferredHeight: 1
                norImage: "image/n-s-circle-btn-bg.png"; pressImage: "image/n-s-circle-btn-press-bg.png"
                text: ""
                focusPolicy: Qt.NoFocus

                enabled: false
            }
*/


