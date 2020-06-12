import QtQuick 2.4
import QtQuick.Controls 2.5
import QtGraphicalEffects 1.14

Popup {
    id: popup
    width: 640
    height: 400
    property alias statusText: statusText
    property alias statusImage: statusImage

    Rectangle {
        id: rectangle
        color: "#ffffff"
        radius: 10
        anchors.fill: parent

        Text {
            id: statusText
            x: 308
            y: 258
            text: qsTr("Please wait...")
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 110
            horizontalAlignment: Text.AlignHCenter
            anchors.horizontalCenter: parent.horizontalCenter
            font.pixelSize: 24
        }

        Image {
            id: statusImage
            x: 270
            y: 118
            width: 100
            height: 100
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: 100
            fillMode: Image.PreserveAspectFit
            source: "assets/loader.png"
        }
    }
}

/*##^##
Designer {
    D{i:3;anchors_y:118}D{i:1;anchors_height:200;anchors_width:200}
}
##^##*/

