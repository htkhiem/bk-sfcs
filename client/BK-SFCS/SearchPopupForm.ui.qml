import QtQuick 2.4
import QtQuick.Controls 2.5

Popup {
    width: 800
    height: 70
    property alias searchButton: searchButton
    property alias searchField: searchField

    Rectangle {
        id: bg
        color: "#ffffff"
        radius: 0
        anchors.fill: parent

        TextField {
            id: searchField
            y: 8
            height: 55
            font.pointSize: 16
            anchors.right: searchButton.left
            anchors.rightMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.verticalCenter: parent.verticalCenter
            placeholderText: qsTr("Item name")
        }

        Button {
            id: searchButton
            x: 615
            y: 19
            width: 80
            height: 55
            text: qsTr("Search")
            font.pointSize: 16
            anchors.right: parent.right
            anchors.rightMargin: 10
            anchors.verticalCenter: parent.verticalCenter
        }
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.8999999761581421}
}
##^##*/

