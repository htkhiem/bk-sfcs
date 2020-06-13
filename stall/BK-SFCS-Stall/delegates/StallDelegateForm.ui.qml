import QtQuick 2.4

Rectangle {
    id: stallBg
    width: 200
    height: 264
    color: "#c8c8c8"
    property alias stallMouseArea: stallMouseArea
    property alias stallImage: stallImage
    property alias stallName: stallName

    Text {
        id: stallName
        x: 85
        anchors.horizontalCenterOffset: 1
        anchors.top: stallImage.bottom
        anchors.topMargin: 28
        anchors.horizontalCenter: parent.horizontalCenter
        horizontalAlignment: Text.AlignHCenter
        font.bold: stallBg.ListView.isCurrentItem ? true : false
        font.pixelSize: 14
    }

    Image {
        id: stallImage
        x: 0
        y: 0
        width: 200
        height: 200
        fillMode: Image.PreserveAspectCrop
    }
    MouseArea {
        id: stallMouseArea
        anchors.fill: parent
    }
}

/*##^##
Designer {
    D{i:1;anchors_x:85;anchors_y:24}
}
##^##*/

