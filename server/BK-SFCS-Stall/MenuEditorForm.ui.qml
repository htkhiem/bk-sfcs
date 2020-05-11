import QtQuick 2.12
import QtQuick.Controls 2.5
import "./delegates"

Page {
    id: menuEditor
    width: 1280
    height: 720
    property alias addButton: addButton
    property alias mgrPswField: mgrPswField
    property alias authorizeButton: authorizeButton
    property alias revertButton: revertButton
    property alias confirmButton: confirmButton
    anchors.fill: parent

    title: qsTr("Menu Editor")

    ScrollView {
        id: scrollView
        anchors.bottomMargin: 10
        clip: true
        anchors.top: instr.bottom
        ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
        ScrollBar.vertical.policy: ScrollBar.AlwaysOn
        anchors.right: parent.right
        anchors.bottom: confirmButton.top
        anchors.left: parent.left
        anchors.topMargin: 10

        Loader {
            id: listViewLoader
            anchors.fill: parent
            source: "MenuEditorSimpleListView.qml"
        }
    }

    Text {
        id: instr
        text: qsTr("You can quickly set items as out of order or not here.You need to authorize yourself with manager rights in order to edit other information.")
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.top: parent.top
        anchors.topMargin: 10
        font.pixelSize: 14
    }

    DelayButton {
        id: confirmButton
        y: 673
        width: 200
        text: qsTr("Confirm changes")
        visible: false
        enabled: false
        delay: 5000
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.left: revertButton.right
        anchors.leftMargin: 10
    }

    DelayButton {
        id: revertButton
        y: 570
        width: 240
        text: qsTr("Revert")
        visible: false
        anchors.left: parent.left
        anchors.bottomMargin: 10
        anchors.bottom: parent.bottom
        anchors.leftMargin: 10
        enabled: false
        delay: 5000
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
        id: mgrPswField
        echoMode: "Password"
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.right: authorizeButton.left
        anchors.rightMargin: 10
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        placeholderText: qsTr("Manager password")
    }

    RoundButton {
        enabled: false
        id: addButton
        text: "+"
        highlighted: false
        flat: false
        anchors.bottom: scrollView.bottom
        anchors.bottomMargin: 10
        anchors.right: parent.right
        anchors.rightMargin: 10
    }
    states: [
        State {
            name: "authorized"

            PropertyChanges {
                target: mgrPswField
                visible: false
            }

            PropertyChanges {
                target: confirmButton
                visible: true
            }

            PropertyChanges {
                target: revertButton
                visible: true
            }

            PropertyChanges {
                target: authorizeButton
                visible: false
            }

            PropertyChanges {
                target: listViewLoader
                source: "MenuEditorFullListView.qml"
            }
            PropertyChanges {
                target: addButton
                enabled: true
            }
        }
    ]
}

/*##^##
Designer {
    D{i:0;formeditorZoom:1.5}D{i:3;anchors_x:589}D{i:4;anchors_x:589}D{i:5;anchors_x:30}
D{i:6;anchors_x:30}D{i:10;anchors_x:589}D{i:11;anchors_x:30}D{i:12;anchors_x:30}D{i:9;anchors_x:589}
}
##^##*/

