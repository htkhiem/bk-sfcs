import QtQuick 2.4
import QtQuick.Controls 2.12

Button {
    height: 70
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

