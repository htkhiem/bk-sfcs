import QtQuick 2.4
import QtGraphicalEffects 1.14

Item {
    width: 200
    height: 320
    property alias itemPrice: itemPrice
    property alias itemMouseArea: itemMouseArea
    property alias itemImage: itemImage
    property alias itemName: itemName
    Rectangle {
        id: itemBg
        width: parent.width
        height: parent.height
        color: "#ffffff"
        radius: 10
    }
    DropShadow {
        anchors.fill: parent
        horizontalOffset: 0
        verticalOffset: 3
        radius: 8.0
        samples: 12
        color: "#80000000"
        source: itemBg
        cached: true
    }
    Text {
        id: itemName
        x: 85
        anchors.horizontalCenterOffset: 1
        anchors.top: itemImage.bottom
        anchors.topMargin: 28
        anchors.horizontalCenter: itemBg.horizontalCenter
        horizontalAlignment: Text.AlignHCenter
        font.bold: false
        font.pixelSize: 14
    }

    Rectangle {
        id: priceBg
        height: 40
        color: "#4caf50"
        radius: 5
        anchors.bottom: itemBg.bottom
        anchors.bottomMargin: 5
        anchors.right: itemBg.right
        anchors.rightMargin: 5
        anchors.left: itemBg.left
        anchors.leftMargin: 5

        Text {
            id: itemPrice
            x: 145
            y: 7
            color: "#ffffff"
            text: qsTr("Text")
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            font.bold: true
            horizontalAlignment: Text.AlignRight
            font.pixelSize: 16
        }
    }

    MouseArea {
        id: itemMouseArea
        x: 145
        y: 285
        anchors.fill: itemBg
    }
    Image {
        id: itemImage
        x: 0
        width: 190
        height: 190
        anchors.horizontalCenter: itemBg.horizontalCenter
        anchors.top: itemBg.top
        anchors.topMargin: 5
        source: "qrc:/qtquickplugin/images/template_image.png"
        fillMode: Image.PreserveAspectCrop
        layer.enabled: true
        layer.effect: OpacityMask {
            maskSource: Item {
                width: itemImage.width
                height: itemImage.height
                Rectangle {
                    anchors.centerIn: parent
                    width: itemImage.width
                    height: itemImage.height
                    radius: 5
                }
            }
        }
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:1.25}
}
##^##*/

