import QtQuick 2.4
import QtQuick.Controls 2.12

Rectangle {
    id: bg
    width: 1280
    height: 60
    property alias disconnectButton: disconnectButton
    property alias clientIdText: clientIdText
    property alias clientTypeText: clientTypeText
    border.color: "silver"
    border.width: 1

    Text {
        id: clientTypeText
        y: 23
        text: qsTr("Text")
        font.bold: true
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.verticalCenter: parent.verticalCenter
        font.pixelSize: 20
    }

    Text {
        id: clientIdText
        y: 22
        text: qsTr("Text")
        anchors.left: parent.left
        anchors.leftMargin: 120
        anchors.verticalCenter: parent.verticalCenter
        font.pixelSize: 14
    }

    Button {
        id: disconnectButton
        x: 736
        y: 12
        text: qsTr("Disconnect")
        anchors.right: parent.right
        anchors.rightMargin: 20
        anchors.verticalCenter: parent.verticalCenter
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:1.5}
}
##^##*/

