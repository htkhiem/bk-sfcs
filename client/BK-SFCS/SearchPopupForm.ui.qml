import QtQuick 2.4
import QtQuick.Controls 2.5
import QtGraphicalEffects 1.14

Popup {
    id: popup
    width: 600
    height: 70
    property alias searchButton: searchButton
    property alias searchField: searchField
    background: Rectangle {
        anchors.fill: parent
        radius: 10
    }
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

    Row {
        id: row
        anchors.leftMargin: 5
        spacing: 5
        anchors.fill: parent

        TextField {
            id: searchField
            x: 5
            y: 5
            width: 470
            height: 60
            font.pointSize: 16
            placeholderText: qsTr("Item name")
            background: Rectangle {
                radius: 5
                border.color: "#737373"
                border.width: 2
                anchors.fill: parent
            }
        }

        Button {
            id: searchButton
            y: 5
            width: 115
            height: 60
            contentItem: Text {
                text: searchButton.text
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                font.bold: true
                color: "#ffffff"
                font.pointSize: 14
            }
            text: qsTr("Search")
            font.pointSize: 11
            background: Rectangle {
                color: "#2f29d1"
                radius: 5
                anchors.fill: parent
            }
        }
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:3}
}
##^##*/

