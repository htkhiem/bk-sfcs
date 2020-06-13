import QtQuick 2.4
import QtQuick.Controls 2.12
import "./delegates"

Page {
    id: page
    property alias passwordInput: passwordInput
    property alias loginButton: loginButton
    property alias stallSelector: stallSelector
    height: 530
    property alias page: page
    Text {
        id: title
        x: 308
        text: qsTr("BK Food Court")
        horizontalAlignment: Text.AlignHCenter
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 24
        font.pixelSize: 36
    }

    Text {
        id: subtitle
        x: 298
        y: -8
        text: qsTr("Authentication System")
        anchors.horizontalCenterOffset: 0
        horizontalAlignment: Text.AlignHCenter
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: -2
        font.pixelSize: 24
        anchors.top: title.bottom
    }

    Button {
        id: loginButton
        text: qsTr("Login")
        font.pointSize: 12
        autoExclusive: false
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 20
        anchors.top: passwordInput.bottom
        anchors.topMargin: 20
        anchors.right: parent.right
        anchors.rightMargin: 20
        anchors.left: parent.left
        anchors.leftMargin: 20
    }

    TextField {
        id: passwordInput
        font.pointSize: 12
        echoMode: "Password"
        horizontalAlignment: Text.AlignHCenter
        anchors.right: parent.right
        anchors.rightMargin: 20
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.top: scrollView.bottom
        anchors.topMargin: 20
        placeholderText: qsTr("Password")
    }

    ScrollView {
        id: scrollView
        height: 263
        anchors.top: subtitle.bottom
        anchors.topMargin: 20
        anchors.right: parent.right
        anchors.rightMargin: 20
        anchors.left: parent.left
        anchors.leftMargin: 20
        clip: true
        ScrollBar.horizontal.policy: ScrollBar.AlwaysOn
        ScrollBar.vertical.policy: ScrollBar.AlwaysOff

        ListView {
            id: stallSelector
            width: 600
            height: 263
            anchors.rightMargin: 0
            anchors.leftMargin: 0
            anchors.bottomMargin: 0
            anchors.top: parent.top
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.topMargin: 0
            spacing: 10
            cacheBuffer: 5
            orientation: ListView.Horizontal
            delegate: StallDelegate {
                stallName.text: model.modelData.stallName
                stallImage.source: model.modelData.imagePath
            }
            model: stallViewModel
            focus: true
        }
    }
}

/*##^##
Designer {
    D{i:1;anchors_y:34}D{i:2;anchors_y:34}D{i:3;anchors_x:20;anchors_y:399}D{i:4;anchors_x:20;anchors_y:343}
D{i:6;anchors_height:264;anchors_x:146;anchors_y:133}D{i:5;anchors_height:200;anchors_width:200;anchors_x:220;anchors_y:142}
}
##^##*/

