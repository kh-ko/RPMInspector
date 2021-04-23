import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import QmlEnumDef 1.0
import EnumDef 1.0
import FontManager 1.0
import QmlPDListDlgModel 1.0
import "../../control/"
import "../image/"

UiDialog {
    id : dialog

    property var baseWindow : null

    contentHeight: 900; contentWidth: 800
    anchors.centerIn : parent

    signal signalEventNewProduct();

    function loadList()
    {
        listModel.clear()

        for(var i = 0; i < pdListmodel.onCommandGetPDCnt(); i ++)
        {
            var pdNum  = pdListmodel.onCommandGetPDNum(i);
            var pdName = pdListmodel.onCommandGetPDName(i);

            listModel.append({"idx": i, "pdNum":pdNum, "pdName": pdName})
        }

        productList.positionViewAtBeginning()
    }

    QmlPDListDlgModel{
        id : pdListmodel

        Component.onCompleted: {
            loadList();
        }
    }

    contentItem: Item{
        Item{
            id : titleBox
            height: 80; width: parent.width
            anchors.top: parent.top; anchors.horizontalCenter: parent.horizontalCenter

            UiText{
                anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.left; anchors.leftMargin : 20

                text: "제품 목록"
            }

            UiButton{
                height: 52; width: 52
                anchors.verticalCenter: parent.verticalCenter; anchors.right: parent.right; anchors.rightMargin: 20

                norImage: "/ui/image/close-btn-bg.png"
                pressImage: "/ui/image/close-btn-press-bg.png"

                onClicked: {
                    dialog.close();
                }
            }
        }

        ListView{
            id : productList
            width: parent.width - 40
            anchors.top: titleBox.bottom; anchors.bottom: footBox.top; anchors.horizontalCenter: parent.horizontalCenter
            clip : true

            model : ListModel{
                id : listModel
            }

            delegate : Rectangle{
                id : rowItem

                height: 80; width: parent.width
                color: (idx % 2) == 0 ? "#19000000" : "#59FFFFFF"

                UiRadio{
                    id : selRadio
                    height: 50; width: 50;
                    anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.left; anchors.leftMargin: 20

                    checkable: false
                    checked: pdNum ===  pdListmodel.mCurrPDNum
                }

                MouseArea{
                    anchors.fill: parent

                    onClicked: {
                        var ret = pdListmodel.onCommandSelectPD(pdNum)

                        if(ret !== "")
                            baseWindow.showToast(ret)
                    }
                }

                UiText{
                    anchors.verticalCenter: parent.verticalCenter; anchors.left: selRadio.right; anchors.leftMargin: 20
                    color: "#5E6874"
                    text : pdNum + " " + pdName
                }

                UiButton{
                    height: 70; width: 200
                    anchors.verticalCenter: parent.verticalCenter; anchors.right: parent.right; anchors.rightMargin: 20

                    norImage: "/ui/image/btn-bg.png"
                    pressImage: "/ui/image/btn-press-bg.png"

                    text: "삭제"

                    onClicked: {
                        var dlg = confirmBox.createObject(panel,{"messageText":"선택하신 제품설정을 삭제하시겠습니까?", "userData" : pdNum})
                        dlg.open()
                    }
                }
            }
        }

        Item{
            id : footBox
            height: 80; width: parent.width
            anchors.bottom: parent.bottom; anchors.horizontalCenter: parent.horizontalCenter

            UiButton{
                height: 70; width: 200
                anchors.verticalCenter: parent.verticalCenter; anchors.horizontalCenter: parent.horizontalCenter

                norImage: "/ui/image/btn-bg.png"
                pressImage: "/ui/image/btn-press-bg.png"

                text: "새 제품 추가"

                onClicked: {
                    dialog.signalEventNewProduct()
                    dialog.close();
                }
            }
        }
    }

    Component{
        id : confirmBox

        UiComfirmBox{
            onSignalEventConfirm: {
                var ret = pdListmodel.onCommandRemovePD(userData)
                if(ret !== "")
                    baseWindow.showToast(ret)
                else{
                    baseWindow.showToast("제품설정이 삭제되었습니다.")
                    loadList()
                }
            }
        }
    }

}
