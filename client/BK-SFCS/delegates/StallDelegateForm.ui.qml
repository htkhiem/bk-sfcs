import QtQuick 2.4
import QtGraphicalEffects 1.14

Item {
    width: 200
    height: 264
    property alias stallMouseArea: stallMouseArea
    property alias stallImage: stallImage
    property alias stallName: stallName
    property alias gradEnd: gradEnd
    property alias gradStart: gradStart

    Rectangle {
        id: stallBg
        width: parent.width
        height: parent.height
        color: "#c8c8c8"
        radius: 10
        border.width: 0
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
    DropShadow {
        anchors.fill: parent
        horizontalOffset: 0
        verticalOffset: 3
        radius: 8.0
        samples: 12
        color: "#80000000"
        source: stallBg
        cached: true
    }
    Text {
        id: stallName
        x: 85
        verticalAlignment: Text.AlignVCenter
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
        width: 190
        height: 190
        anchors.top: parent.top
        anchors.topMargin: 5
        anchors.horizontalCenter: parent.horizontalCenter
        source: "qrc:/qtquickplugin/images/template_image.png"
        fillMode: Image.PreserveAspectCrop
        layer.enabled: true
        layer.effect: OpacityMask {
            maskSource: Item {
                width: stallImage.width
                height: stallImage.height
                Rectangle {
                    anchors.centerIn: parent
                    width: stallImage.width
                    height: stallImage.height
                    radius: 5
                }
            }
        }
    }
    MouseArea {
        id: stallMouseArea
        anchors.fill: parent
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:2}
}
##^##*/

