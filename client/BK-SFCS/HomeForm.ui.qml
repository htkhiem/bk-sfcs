import QtQuick 2.12
import QtQuick.Controls 2.5
import "./delegates"

Page {
    width: 1280
    height: 400
    property alias stallGrid: stallGrid

    title: qsTr("Select a stall")

    GridView {
        id: stallGrid
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
        model: StallDelegateModel {}
        delegate: StallDelegate {
            stallImage.source: image
            stallName.text: name
        }
    }
}
