import QtQuick 2.4
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3

Page {
    id: page
    width: 1280
    height: 720
    TabBar {
        id: navBar
        width: parent.width
        anchors.top: parent.top
        anchors.topMargin: 0
        currentIndex: 1
        TabButton {
            text: qsTr("Sales report")
        }
        TabButton {
            text: qsTr("Waitlist")
        }
        TabButton {
            text: qsTr("Menu")
        }
    }
    StackLayout {
        id: mainLayout
        width: 1280
        anchors.top: navBar.bottom
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.topMargin: 0
        currentIndex: navBar.currentIndex
        Item {
            id: homeForm
            HomeForm {
                anchors.fill: parent
                z: 0
            }
        }
        Item {
            id: waitListForm
            WaitList {
                anchors.fill: parent
                z: 0
            }
        }
        Item {
            id: menuEditor
            MenuEditor {
                anchors.fill: parent
                z: 0
            }
        }
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.6600000262260437}D{i:7;anchors_height:720;anchors_width:1280}
D{i:5;anchors_height:720;anchors_width:640}
}
##^##*/

