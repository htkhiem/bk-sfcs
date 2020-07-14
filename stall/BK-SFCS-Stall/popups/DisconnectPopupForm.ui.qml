import QtQuick 2.4
import QtQuick.Controls 2.12

Popup {
    id: popup
    width: 400
    height: 100
    modal: true
    closePolicy: Popup.NoAutoClose

    Rectangle {
        id: bg
        color: "#ffffff"
        anchors.fill: parent

        TextInput {
            id: textInput
            text: qsTr("Connection lost. \nPlease restart the application.")
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 20
            anchors.top: parent.top
            anchors.topMargin: 20
            anchors.right: parent.right
            anchors.rightMargin: 20
            anchors.left: parent.left
            anchors.leftMargin: 20
            verticalAlignment: Text.AlignVCenter
            wrapMode: Text.WordWrap
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 20
        }
    }
}

/*##^##
Designer {
    D{i:2;anchors_height:20;anchors_width:80;anchors_x:110;anchors_y:40}D{i:1;anchors_height:200}
}
##^##*/
