import QtQuick 2.4
import QtQuick.Controls 2.12

Popup {
    id: popup
    width: 300
    height: 120
    property alias noButton: noButton
    property alias yesButton: yesButton
    modal: true
    closePolicy: Popup.NoAutoClose

    Rectangle {
        id: bg
        color: "#ffffff"
        anchors.fill: parent

        TextInput {
            id: textInput
            text: qsTr("You have unsaved changes. Exit the editor?")
            anchors.bottom: yesButton.top
            anchors.bottomMargin: 6
            anchors.top: parent.top
            anchors.topMargin: 20
            anchors.right: parent.right
            anchors.rightMargin: 20
            anchors.left: parent.left
            anchors.leftMargin: 20
            verticalAlignment: Text.AlignVCenter
            wrapMode: Text.WordWrap
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 15
        }

        Button {
            id: yesButton
            y: 102
            width: 90
            text: qsTr("Yes, exit")
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 10
            anchors.left: parent.left
            anchors.leftMargin: 10
        }

        Button {
            id: noButton
            y: 102
            text: qsTr("No, take me back")
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 10
            anchors.right: parent.right
            anchors.rightMargin: 10
            anchors.left: yesButton.right
            anchors.leftMargin: 10
        }
    }
}



