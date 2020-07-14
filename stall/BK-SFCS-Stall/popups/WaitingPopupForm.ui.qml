import QtQuick 2.4
import QtQuick.Controls 2.12

Popup {
    width: 300
    height: 100
    modal: true
    closePolicy: Popup.NoAutoClose

    Rectangle {
        id: bg
        color: "#ffffff"
        anchors.fill: parent

        TextInput {
            id: textInput
            x: 110
            y: 40
            width: 80
            height: 20
            text: qsTr("Please wait...")
            horizontalAlignment: Text.AlignHCenter
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            font.pixelSize: 20
        }
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:1.25}
}
##^##*/
