import QtQuick 2.4
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3

Page {
    id: page
    width: 500
    height: 720
    TabBar {
        id: navBar
        width: parent.width
        anchors.top: parent.top
        anchors.topMargin: 0
        currentIndex: 0
        TabButton {
            text: qsTr("Clients")
            onClicked: tabLoader.source = "client_tab/ClientList.qml"
        }
        TabButton {
            text: qsTr("Stall list")
            onClicked: tabLoader.source = "stall_tab/StallList.qml"
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
        source: "client_tab/ClientList.qml"
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.6600000262260437}
}
##^##*/

