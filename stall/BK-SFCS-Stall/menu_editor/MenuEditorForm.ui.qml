import QtQuick 2.12
import QtQuick.Controls 2.5
import QtGraphicalEffects 1.0

Page {
    id: menuEditor
    width: 1280
    height: 720
    property alias listViewLoader: listViewLoader
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
            sourceComponent: restrictedListView
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
        delay: 1000
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
        delay: 2000
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
        id: addButton
        enabled: false
        width: 40
        height: width
        background: Rectangle {
            width: parent.width
            height: parent.height
            radius: width / 2
            color: "#0033cc"
            opacity: enabled ? 1 : 0.2
        }
        contentItem: Text {
            text: parent.text
            font: parent.font
            opacity: enabled ? 1.0 : 0.2
            color: "#ffffff"
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            elide: Text.ElideRight
        }

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
                sourceComponent: fullListView
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
    D{i:0;formeditorZoom:0.5}
}
##^##*/

