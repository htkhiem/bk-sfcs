import QtQuick 2.4
import QtQuick.Controls 2.5
import QtGraphicalEffects 1.14

Popup {
    id: popup
    property alias name: name
    width: 670
    height: 670
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
            source: "qrc:/qtquickplugin/images/template_image.png"
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

            Text {
                id: name
                x: 311
                y: -476
                color: "#ffffff"
                text: qsTr("Text")
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: parent.top
                anchors.topMargin: 24
                font.pixelSize: 24
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
        }
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.5}
}
##^##*/

