import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3

ApplicationWindow {
    id: window
    visible: true
    width: 1280
    height: 720
    title: qsTr("BK-SFCS Stall Manager")
    Main {
        id: navLayout
        anchors.fill: parent
    }
}
