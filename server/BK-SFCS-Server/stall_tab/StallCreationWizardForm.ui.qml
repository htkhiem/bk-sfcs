import QtQuick 2.4
import QtQuick.Controls 2.12

Popup {
    id: popup
    width: 400
    height: 400
    property alias popup: popup
    property alias mgrPswField: mgrPswField
    property alias pswField: pswField
    property alias changeImageButton: changeImageButton
    property alias nameField: nameField
    property alias image: image
    property alias finishButton: finishButton
    modal: true

    Rectangle {
        id: rectangle
        x: 67
        y: 152
        width: 200
        height: 200
        color: "#ffffff"
        anchors.fill: parent

        Text {
            id: popupTitle
            text: qsTr("New Stall Wizard")
            font.italic: false
            anchors.left: parent.left
            anchors.leftMargin: 15
            anchors.top: parent.top
            anchors.topMargin: 15
            font.pixelSize: 15
        }

        Button {
            id: finishButton
            height: 30
            text: qsTr("Confirm")
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 15
            anchors.right: parent.right
            anchors.rightMargin: 15
            anchors.left: parent.left
            anchors.leftMargin: 15
        }

        Image {
            id: image
            width: 100
            height: 100
            anchors.top: popupTitle.bottom
            anchors.topMargin: 5
            anchors.left: parent.left
            anchors.leftMargin: 15
            source: "qrc:/qtquickplugin/images/template_image.png"
            fillMode: Image.PreserveAspectFit
        }

        TextField {
            id: nameField
            font.bold: true
            anchors.bottom: changeImageButton.top
            anchors.bottomMargin: 5
            anchors.right: parent.right
            anchors.rightMargin: 15
            anchors.left: image.right
            anchors.leftMargin: 5
            anchors.top: popupTitle.bottom
            anchors.topMargin: 5
            maximumLength: 32
            placeholderText: qsTr("Stall name (max. 32 characters)")
        }

        Button {
            id: changeImageButton
            y: 109
            height: 30
            text: qsTr("Change image")
            anchors.bottom: image.bottom
            anchors.bottomMargin: 0
            anchors.right: parent.right
            anchors.rightMargin: 15
            anchors.left: image.right
            anchors.leftMargin: 6
        }

        TextField {
            id: pswField
            anchors.top: pswLabel.bottom
            anchors.topMargin: 5
            anchors.right: parent.right
            anchors.rightMargin: 15
            anchors.left: parent.left
            anchors.leftMargin: 15
            echoMode: TextField.Password
            placeholderText: qsTr("Login password")
        }

        Text {
            id: pswLabel
            y: 166
            text: qsTr("Login password")
            anchors.left: parent.left
            anchors.leftMargin: 15
            font.pixelSize: 12
        }

        TextField {
            id: mgrPswField
            anchors.rightMargin: 15
            anchors.right: parent.right
            anchors.leftMargin: 15
            anchors.left: parent.left
            anchors.top: mgrPswLabel.bottom
            anchors.topMargin: 5
            echoMode: TextField.Password
            placeholderText: qsTr("Manager password")
        }

        Text {
            id: mgrPswLabel
            y: 242
            text: qsTr("Management password")
            anchors.leftMargin: 15
            font.pixelSize: 12
            anchors.left: parent.left
        }
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:1.25}D{i:2;anchors_x:27;anchors_y:34}D{i:4;anchors_x:15;anchors_y:40}
D{i:5;anchors_x:132;anchors_y:39}D{i:6;anchors_x:121}D{i:7;anchors_x:15;anchors_y:187}
D{i:8;anchors_x:15}D{i:9;anchors_x:15;anchors_y:187}D{i:10;anchors_x:15}
}
##^##*/

