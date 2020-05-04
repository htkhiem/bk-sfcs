import QtQuick 2.4

Rectangle {
    id: bg
    width: 100
    height: 100
    color: "#737373"
    radius: 10
    property alias categorySymbol: categorySymbol
    property alias mouseArea: mouseArea
    property alias categoryName: categoryName

    Text {
        id: categoryName
        x: 38
        y: 77
        text: qsTr("Text")
        horizontalAlignment: Text.AlignHCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        anchors.horizontalCenter: parent.horizontalCenter
        font.pixelSize: 14
    }

    Text {
        id: categorySymbol
        x: 32
        y: 8
        color: "#ffffff"
        text: qsTr("C")
        anchors.top: parent.top
        anchors.topMargin: 8
        horizontalAlignment: Text.AlignHCenter
        anchors.horizontalCenter: parent.horizontalCenter
        font.pixelSize: 48
    }
    MouseArea {
        id: mouseArea
        x: 0
        y: 0
        anchors.fill: parent
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:8}D{i:2;anchors_y:8}D{i:3;anchors_y:8}
}
##^##*/

