import QtQuick 2.4
import QtQuick.Controls 2.12

Rectangle {
    id: bg
    width: 1280
    height: 180
    property alias nameText: nameText
    property alias qtyNumber: qtyNumber
    property alias itemImage: itemImage
    property alias bg: bg
    border.color: "#8a8a8a"
    border.width: 1

    Image {
        id: itemImage
        width: itemImage.height
        height: bg.height - 2 * anchors.topMargin
        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 10
        fillMode: Image.PreserveAspectFit
        source: "qrc:/qtquickplugin/images/template_image.png"
    }

    Frame {
        id: qtyFrame
        width: 150
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        anchors.left: itemImage.right
        anchors.leftMargin: 10
        anchors.top: parent.top
        anchors.topMargin: 10

        Text {
            id: qtyLabel
            color: "#737373"
            text: qsTr("QUANTITY")
            font.bold: true
            anchors.horizontalCenter: parent.horizontalCenter
            font.pixelSize: 15
        }

        Text {
            id: qtyNumber
            text: qsTr("1")
            horizontalAlignment: Text.AlignHCenter
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            font.pixelSize: 48
        }
    }

    Button {
        id: stepButton
        x: 523
        height: 100
        text: qsTr("Hold")
        font.bold: true
        wheelEnabled: false
        hoverEnabled: true
        enabled: true
        font.pointSize: 15
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.top: parent.top
        anchors.topMargin: 10
    }

    Button {
        id: rejectButton
        x: 1170
        text: qsTr("Reject")
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        font.pointSize: 15
        anchors.top: stepButton.bottom
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.topMargin: 10
    }

    Frame {
        id: nameFrame
        anchors.right: priceFrame.left
        anchors.rightMargin: 10
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.leftMargin: 10
        anchors.left: qtyFrame.right
        anchors.topMargin: 10
        Text {
            id: nameLabel
            color: "#737373"
            text: qsTr("NAME")
            font.pixelSize: 15
            anchors.horizontalCenter: parent.horizontalCenter
            font.bold: true
        }

        Text {
            id: nameText
            text: qsTr("Item name")
            anchors.right: parent.right
            anchors.rightMargin: 10
            anchors.left: parent.left
            anchors.leftMargin: 10
            horizontalAlignment: Text.AlignHCenter
            anchors.verticalCenter: parent.verticalCenter
            font.pixelSize: 24
        }
        anchors.bottomMargin: 10
    }

    Frame {
        id: priceFrame
        x: 964
        width: 200
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.right: stepButton.left
        anchors.rightMargin: 10
        anchors.topMargin: 10
        Text {
            id: priceLabel
            color: "#737373"
            text: qsTr("PRICE IN VND")
            font.pixelSize: 15
            anchors.horizontalCenter: parent.horizontalCenter
            font.bold: true
        }

        Text {
            id: priceText
            color: "#1e7e25"
            text: qsTr("10000")
            verticalAlignment: Text.AlignBottom
            horizontalAlignment: Text.AlignHCenter
            anchors.right: parent.right
            anchors.rightMargin: 10
            anchors.left: parent.left
            anchors.leftMargin: 10
            font.bold: false
            anchors.verticalCenter: parent.verticalCenter
            font.pixelSize: 36
        }
        anchors.bottomMargin: 10
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.75}D{i:2;anchors_height:200;anchors_x:137;anchors_y:10}D{i:5;anchors_y:132}
D{i:6;anchors_height:100;anchors_y:132}D{i:7;anchors_height:200;anchors_width:150;anchors_x:137;anchors_y:10}
D{i:10;anchors_height:200;anchors_width:150;anchors_x:137;anchors_y:10}
}
##^##*/

