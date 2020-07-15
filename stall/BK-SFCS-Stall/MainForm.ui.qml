import QtQuick 2.4
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import "./menu_editor"

Page {
    id: page
    width: 1280
    height: 720
    property alias tabLoader: tabLoader
    property alias stallEditorTabButton: stallEditorTabButton
    property alias menuEditorTabButton: menuEditorTabButton
    property alias waitlistTabButton: waitlistTabButton
    property alias salesTabButton: salesTabButton
    TabBar {
        id: navBar
        width: parent.width
        anchors.top: parent.top
        anchors.topMargin: 0
        currentIndex: 1
        TabButton {
            id: salesTabButton
            text: qsTr("Sales report")
        }
        TabButton {
            id: waitlistTabButton
            text: qsTr("Waitlist")
        }
        TabButton {
            id: menuEditorTabButton
            text: qsTr("Menu")
        }
        TabButton {
            id: stallEditorTabButton
            text: qsTr("Stall")
        }
    }
    Loader {
        id: tabLoader
        width: 1280
        anchors.top: navBar.bottom
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.topMargin: 0
        source: "order_process/WaitList.qml"
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.6600000262260437}D{i:6;anchors_height:720;anchors_width:640}
}
##^##*/

