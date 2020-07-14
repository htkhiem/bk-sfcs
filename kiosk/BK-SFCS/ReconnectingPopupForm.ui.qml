import QtQuick 2.4
import QtQuick.Controls 2.5
import QtGraphicalEffects 1.14

Popup {
    id: popup
    width: 320
    height: 320
    property alias statusText: statusText
    property alias statusImage: statusImage

    modal: true
    closePolicy: Popup.NoAutoClose

    background: Rectangle {
        opacity: 0
    }

    Rectangle {
        id: rectangle
        color: "#ffffff"
        radius: 10
        anchors.fill: parent

        AnimatedImage {
            id: statusImage
            x: 270
            y: 118
            width: 180
            height: 180
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: 55
            fillMode: Image.PreserveAspectFit
            source: "assets/loader_animated.gif"
        }
        Text {
            id: statusText
            x: 308
            y: 258
            text: qsTr("Reconnecting to server...")
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 75
            horizontalAlignment: Text.AlignHCenter
            anchors.horizontalCenter: parent.horizontalCenter
            font.pixelSize: 24
        }
    }
}
