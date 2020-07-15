import QtQuick 2.14
import QtQuick.Controls 2.5
import "./delegates"
import QtGraphicalEffects 1.0

Page {
    property alias gridView: gridView
    property alias listView: listView
    property alias pageBg: fastBlurredBg
    width: 1280
    height: 720
    Rectangle {
        id: bg
        anchors.fill: parent
        FastBlur {
            id: bgBlur
            anchors.fill: parent
            source: Image {
                id: fastBlurredBg
                fillMode: Image.PreserveAspectCrop
                anchors.fill: parent
            }

            radius: 64
            cached: true
        }

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
                    model: categoryViewModel
                    delegate: CategoryDelegate {
                        text: model.modelData.name
                        image.source: symbol
                        gradStart.color: model.modelData.colorStart
                        gradEnd.color: model.modelData.colorEnd
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
                    model: menuViewModel
                    cellHeight: 338
                    cellWidth: 210
                    delegate: MenuDelegate {
                        itemPrice.text: model.modelData.price
                        itemName.text: model.modelData.name
                        matching: model.modelData.matching
                        oos: model.modelData.isOOS
                    }
                }
            }
        }
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.8999999761581421}
}
##^##*/

