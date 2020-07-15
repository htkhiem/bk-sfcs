import QtQuick 2.4
import QtQuick.Controls 2.12

Rectangle {
    id: bg
    width: 1200
    height: 100
    property alias removeButton: removeButton
    property alias disconnectButton: disconnectButton
    property alias onlineStatus: onlineStatus
    property alias nameText: nameText
    property alias image: image
    border.color: "silver"
    border.width: 1
    Image {
        id: image
        y: 0
        width: 90
        height: 90
        anchors.left: parent.left
        anchors.leftMargin: 5
        anchors.verticalCenter: parent.verticalCenter
        fillMode: Image.PreserveAspectFit
        source: "qrc:/qtquickplugin/images/template_image.png"
    }

    Text {
        id: nameText
        y: 43
        text: qsTr("Text")
        anchors.left: image.right
        anchors.leftMargin: 10
        anchors.verticalCenter: parent.verticalCenter
        font.pixelSize: 15
    }

    Rectangle {
        id: onlineStatus
        x: 177
        y: 27
        width: 15
        height: width
        color: "#73e318"
        radius: width / 2
        visible: false
        anchors.bottom: image.bottom
        anchors.bottomMargin: -3
        anchors.right: image.right
        anchors.rightMargin: -3
        border.color: "#ffffff"
        border.width: 3
    }

    Button {
        id: removeButton
        x: 1068
        y: 30
        text: qsTr("Remove")
        font.bold: false
        anchors.right: parent.right
        anchors.rightMargin: 30
        anchors.verticalCenter: parent.verticalCenter
    }

    Button {
        id: disconnectButton
        x: 954
        y: 30
        text: qsTr("Disconnect")
        enabled: false
        anchors.right: removeButton.left
        anchors.rightMargin: 10
        anchors.verticalCenter: parent.verticalCenter
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.6600000262260437}D{i:1;anchors_x:0}D{i:2;anchors_x:136}
}
##^##*/

