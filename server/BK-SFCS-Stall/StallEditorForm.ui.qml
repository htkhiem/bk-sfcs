import QtQuick 2.12
import QtQuick.Controls 2.5

Page {
    id: page
    width: 1280
    height: 720
    property alias stallMgmtPswConfField: stallMgmtPswConfField
    property alias stallMgmtPswField: stallMgmtPswField
    property alias confirmButton: confirmButton
    property alias authPswField: authPswField
    property alias authorizeButton: authorizeButton
    property alias stallPswConfField: stallPswConfField
    property alias stallPswField: stallPswField
    property alias stallNameField: stallNameField
    property alias bigImage: bigImage
    property alias changeImageButton: changeImageButton

    Image {
        id: bigImage
        width: 400
        height: 400
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.top: parent.top
        anchors.topMargin: 20
        fillMode: Image.PreserveAspectFit
    }

    Button {
        id: changeImageButton
        enabled: false
        x: 20
        width: 400
        text: qsTr("Change image")
        anchors.top: bigImage.bottom
        anchors.topMargin: 10
        anchors.horizontalCenter: bigImage.horizontalCenter
    }

    TextField {
        enabled: false
        id: stallNameField
        anchors.right: parent.right
        anchors.rightMargin: 20
        anchors.left: bigImage.right
        anchors.leftMargin: 20
        anchors.top: parent.top
        anchors.topMargin: 20
        placeholderText: qsTr("Text Field")
    }

    TextField {
        enabled: false
        id: stallPswField
        anchors.right: parent.right
        anchors.rightMargin: 20
        echoMode: "Password"
        anchors.left: bigImage.right
        anchors.leftMargin: 20
        anchors.top: stallNameField.bottom
        anchors.topMargin: 20
        placeholderText: qsTr("New password")
    }

    TextField {
        enabled: false
        id: stallPswConfField
        anchors.right: parent.right
        anchors.rightMargin: 20
        echoMode: "Password"
        anchors.top: stallPswField.bottom
        anchors.topMargin: 10
        anchors.left: bigImage.right
        anchors.leftMargin: 20
        placeholderText: qsTr("Confirm new password")
    }
    Button {
        id: authorizeButton
        x: 30
        y: 849
        text: qsTr("Authorize editing")
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
    }

    TextField {
        visible: true
        id: authPswField
        echoMode: "Password"
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.right: authorizeButton.left
        anchors.rightMargin: 10
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        placeholderText: qsTr("Manager password")
    }

    Button {
        id: confirmButton
        y: 611
        height: 53
        text: qsTr("Confirm changes")
        visible: false
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 10
    }

    TextField {
        id: stallMgmtPswField
        anchors.right: parent.right
        enabled: false
        anchors.top: stallPswConfField.bottom
        echoMode: "Password"
        placeholderText: qsTr("New manager password")
        anchors.topMargin: 20
        anchors.left: bigImage.right
        anchors.rightMargin: 20
        anchors.leftMargin: 20
    }

    TextField {
        id: stallMgmtPswConfField
        x: 1046
        y: 249
        anchors.right: parent.right
        enabled: false
        anchors.top: stallMgmtPswField.bottom
        echoMode: "Password"
        placeholderText: qsTr("Confirm new manager password")
        anchors.topMargin: 10
        anchors.left: bigImage.right
        anchors.rightMargin: 20
        anchors.leftMargin: 20
    }
    states: [
        State {
            name: "authorized"
            PropertyChanges {
                target: changeImageButton
                enabled: true
            }
            PropertyChanges {
                target: stallNameField
                enabled: true
            }
            PropertyChanges {
                target: stallPswField
                enabled: true
            }
            PropertyChanges {
                target: stallPswConfField
                enabled: true
            }
            PropertyChanges {
                target: stallMgmtPswField
                enabled: true
            }
            PropertyChanges {
                target: stallMgmtPswConfField
                enabled: true
            }
            PropertyChanges {
                target: confirmButton
                visible: true
            }
            PropertyChanges {
                target: authPswField
                visible: false
            }
            PropertyChanges {
                target: authorizeButton
                visible: false
            }
        }
    ]
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.6600000262260437}D{i:1;anchors_x:23;anchors_y:22}D{i:2;anchors_y:434}
D{i:3;anchors_x:432;anchors_y:20}D{i:4;anchors_x:432;anchors_y:66}D{i:5;anchors_x:440;anchors_y:124}
D{i:6;anchors_x:30}D{i:8;anchors_width:1260;anchors_x:10}D{i:9;anchors_x:432;anchors_y:66}
D{i:10;anchors_x:440;anchors_y:124}
}
##^##*/

