import QtQuick 2.7
import QtQuick.Controls 2.12

Button {
    id: button
    contentItem: Text {
        text: button.text
        font: button.font
        color: "#FFFFFFFF"
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        elide: Text.ElideRight
    }
    height: 70
    font.family: "Arial"
    font.pointSize: 15
    width: 200
    property alias gradEnd: gradEnd
    property alias gradStart: gradStart
    checkable: true
    checked: true

    background: Rectangle {
        anchors.fill: parent
        radius: 10
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
}

/*##^##
Designer {
    D{i:0;formeditorZoom:1.75}
}
##^##*/

