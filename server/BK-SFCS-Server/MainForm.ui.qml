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
            text: qsTr("Clients")
            onClicked: tabLoader.source = "Home.qml"
        }
        TabButton {
            text: qsTr("Stall list")
            onClicked: tabLoader.source = "order_process/WaitList.qml"
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
        source: "ClientList.qml"
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.6600000262260437}
}
##^##*/

