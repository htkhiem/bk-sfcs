import QtQuick 2.4
import QtQuick.Controls 2.12

Rectangle {
    property alias loader: loader
    border.color: "silver"
    border.width: 1

    Loader {
        id: loader
        source: chart
        anchors.fill: parent
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
