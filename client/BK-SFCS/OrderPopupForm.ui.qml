import QtQuick 2.4
import QtQuick.Controls 2.5
import QtGraphicalEffects 1.14

Popup {
    id: popup
    property alias name: name
    width: 670
    height: 670
    property alias desc: desc
    property alias estTime: estTime
    property alias paymentMethodBox: paymentMethodBox
    rightPadding: 0
    leftPadding: 0
    bottomPadding: 0
    topPadding: 0
    padding: 0
    margins: 0
    rightMargin: 0
    leftMargin: 0
    bottomMargin: 0
    topMargin: 0
    property alias orderButton: orderButton
    property alias quantitySelector: quantitySelector
    property alias image: image
    background: Rectangle {
        radius: 10
        anchors.fill: parent
    }
    Rectangle {
        id: popupBg
        color: "#00000000"
        radius: 10
        anchors.fill: parent

        DelayButton {
            id: orderButton
            y: 579
            height: 107
            text: qsTr("Order")
            delay: 2000
            font.bold: true
            font.pointSize: 12
            anchors.right: parent.right
            anchors.rightMargin: 5
            anchors.left: infoBg.right
            anchors.leftMargin: 5
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 5
        }

        Tumbler {
            id: quantitySelector
            anchors.bottom: paymentMethodBox.top
            anchors.bottomMargin: 5
            anchors.right: parent.right
            anchors.rightMargin: 5
            anchors.top: parent.top
            anchors.topMargin: 5
            anchors.left: image.right
            anchors.leftMargin: 5
            font.pointSize: 18
            font.bold: false
            wheelEnabled: true
            visible: true
            model: [1, 2, 3, 4, 5]
        }

        Image {
            id: image
            width: 500
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 5
            anchors.left: parent.left
            anchors.leftMargin: 5
            anchors.top: parent.top
            anchors.topMargin: 5
            fillMode: Image.PreserveAspectCrop
            layer.enabled: true
            layer.effect: OpacityMask {
                maskSource: Item {
                    width: image.width
                    height: image.height
                    Rectangle {
                        anchors.centerIn: parent
                        width: image.width
                        height: image.height
                        radius: 5
                    }
                }
            }
        }

        Rectangle {
            id: infoBg
            y: 500
            width: 500
            height: popup.height / 4
            color: "#cc000000"
            radius: 5
            anchors.left: parent.left
            anchors.leftMargin: 5
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 5

            ScrollView {
                id: scrollView
                topPadding: 0
                padding: 0
                spacing: 0
                anchors.rightMargin: 10
                anchors.leftMargin: 10
                anchors.bottomMargin: 10
                anchors.topMargin: 10
                anchors.fill: parent

                Text {
                    id: desc
                    color: "#ffffff"
                    text: qsTr("Text")
                    anchors.left: parent.left
                    anchors.leftMargin: 0
                    anchors.right: parent.right
                    anchors.rightMargin: 0
                    anchors.top: estTime.bottom
                    anchors.topMargin: 3
                    wrapMode: Text.WordWrap
                    styleColor: "#ffffff"
                    font.pixelSize: 14
                }

                Text {
                    id: estTime
                    color: "#ffffff"
                    text: qsTr("Text")
                    anchors.left: parent.left
                    anchors.leftMargin: 0
                    anchors.top: name.bottom
                    anchors.topMargin: -1
                    font.italic: true
                    font.pixelSize: 16
                }

                Text {
                    id: name
                    x: 0
                    y: 0
                    color: "#ffffff"
                    text: qsTr("Text")
                    anchors.right: parent.right
                    anchors.rightMargin: 0
                    anchors.top: parent.top
                    anchors.topMargin: 0
                    anchors.left: parent.left
                    anchors.leftMargin: 0
                    wrapMode: Text.WordWrap
                    font.bold: true
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignLeft
                    font.pixelSize: 24
                }
            }
        }

        ComboBox {
            id: paymentMethodBox
            y: 534
            width: 155
            height: 55
            anchors.bottom: orderButton.top
            anchors.bottomMargin: 5
            anchors.right: parent.right
            anchors.rightMargin: 5
            anchors.left: image.right
            anchors.leftMargin: 5
            background: Rectangle {
                color: "#c6c6c6"
                radius: 5
                anchors.fill: parent
            }
            model: ListModel {
                ListElement {
                    key: "Cash over counter"
                    value: 123
                }
                ListElement {
                    key: "Momo Wallet"
                    value: 456
                }
                ListElement {
                    key: "Lamb sauce"
                    value: 789
                }
            }
            textRole: "key"
        }
    }
}

/*##^##
Designer {
    D{i:11;anchors_x:0;anchors_y:0}D{i:12;anchors_x:0;anchors_y:0}D{i:10;anchors_height:200;anchors_width:200}
}
##^##*/

