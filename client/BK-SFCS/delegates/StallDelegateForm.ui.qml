import QtQuick 2.4

Rectangle {
    id: stallBg
    width: 200
    height: 264
    color: "#c8c8c8"
    property alias stallMouseArea: stallMouseArea
    property alias stallImage: stallImage
    property alias stallName: stallName
    property alias gradEnd: gradEnd
    property alias gradStart: gradStart
    Text {
        id: stallName
        x: 85
        anchors.horizontalCenterOffset: 1
        anchors.top: stallImage.bottom
        anchors.topMargin: 28
        anchors.horizontalCenter: parent.horizontalCenter
        horizontalAlignment: Text.AlignHCenter
        font.bold: false
        font.pixelSize: 14
    }

    Image {
        id: stallImage
        x: 0
        y: 0
        width: 200
        height: 200
        source: "qrc:/qtquickplugin/images/template_image.png"
        fillMode: Image.PreserveAspectFit
    }
    MouseArea {
        id: stallMouseArea
        anchors.fill: parent
    }
    gradient: Gradient {
        GradientStop {
            id: gradStart
            position: 0
        }
        GradientStop {
            id: gradEnd
            position: 1
        }
    }
}

/*##^##
Designer {
    D{i:1;anchors_x:85;anchors_y:24}
}
##^##*/

