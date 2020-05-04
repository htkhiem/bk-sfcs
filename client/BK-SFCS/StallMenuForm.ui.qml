import QtQuick 2.14
import QtQuick.Controls 2.5
import "./delegates"

Page {
    id: page
    width: 1280
    height: 720
    property alias listView: listView
    property alias gridView: gridView
    ScrollView {
        id: scrollView
        spacing: 10
        contentHeight: 1000
        contentWidth: 1280
        anchors.fill: parent

        Column {
            id: column
            padding: 10
            rightPadding: 10
            leftPadding: 10
            topPadding: 10
            anchors.fill: parent
            spacing: 10

            ListView {
                id: listView
                width: 1280
                height: 70
                contentWidth: 110
                spacing: 10
                cacheBuffer: 10
                contentHeight: 100
                rightMargin: 0
                leftMargin: 0
                bottomMargin: 0
                topMargin: 0
                orientation: ListView.Horizontal
                model: CategoryDelegateModel {}
                delegate: Button {
                    height: 70
                    width: 200
                    text: symbol + ' ' + name
                    font.pointSize: 16
                    font.family: "Arial"
                    checkable: true
                    checked: true
                    background: CategoryDelegate {
                        text: symbol + ' ' + name
                        gradStart.color: colorStart
                        gradEnd.color: colorEnd
                    }
                }
            }

            GridView {
                id: gridView
                width: 1280
                height: 720
                boundsMovement: Flickable.FollowBoundsBehavior
                boundsBehavior: Flickable.StopAtBounds
                flickableDirection: Flickable.AutoFlickDirection
                contentWidth: gridView.width
                contentHeight: gridView.height

                cacheBuffer: 10
                model: MenuDelegateModel {}
                cellHeight: 338
                cellWidth: 210
                delegate: MenuDelegate {
                    itemPrice.text: price
                    itemImage.source: image
                    itemName.text: name
                }
            }
        }
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:2}D{i:2;anchors_height:400;anchors_width:200}
}
##^##*/

