import QtQuick 2.12
import QtQuick.Controls 2.5
import "./delegates"

Page {
    id: page
    width: 1280
    height: 720
    property alias menuGrid: menuGrid

    // title:
    GridView {
        id: menuGrid
        anchors.rightMargin: 10
        anchors.leftMargin: 10
        anchors.bottomMargin: 10
        anchors.topMargin: 10
        bottomMargin: 5
        cacheBuffer: 16
        rightMargin: 5
        leftMargin: 5
        topMargin: 5
        cellHeight: 284
        cellWidth: 210
        anchors.fill: parent
        model: MenuDelegateModel {}
        delegate: MenuDelegate {
            itemName.text: name
            itemImage.source: image
            itemPrice.text: price
        }
    }
}
