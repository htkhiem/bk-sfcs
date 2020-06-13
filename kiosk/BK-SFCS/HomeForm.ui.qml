import QtQuick 2.12
import QtQuick.Controls 2.5
import "./delegates"

Page {
    width: 1280
    height: 720
    property alias stallGrid: stallGrid
    background: Rectangle {
        anchors.fill: parent
        color: "#ffffd3"
    }
    title: qsTr("Select a stall")

    GridView {
        id: stallGrid
        flickableDirection: Flickable.AutoFlickDirection
        anchors.rightMargin: 10
        anchors.leftMargin: 10
        anchors.bottomMargin: 10
        anchors.topMargin: 10
        bottomMargin: 5
        cacheBuffer: 16
        rightMargin: 5
        leftMargin: 5
        topMargin: 5
        cellHeight: 274
        cellWidth: 210
        anchors.fill: parent
        model: stallViewModel
        delegate: StallDelegate {
            stallName.text: model.modelData.stallName
            gradStart.color: "#ffffff"
            gradEnd.color: "#ffffff"
        }
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.6600000262260437}
}
##^##*/
