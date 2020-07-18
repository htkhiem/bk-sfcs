import QtQuick 2.12
import QtQuick.Controls 2.5
import "./delegates"

Page {
    id: page
    width: 1280
    height: 720
    property alias dataRangeSlider: dataRangeSlider
    property alias rejectBox: rejectBox
    property alias respBox: respBox
    property alias procBox: procBox
    property alias qtyBox: qtyBox
    property alias advancedExportButton: advancedExportButton
    property alias timeGraph: timeGraph
    property alias rejectGraph: rejectGraph
    property alias qtyGraph: qtyGraph
    property alias dataRangeEnd: dataRangeEnd
    property alias dataRangeStart: dataRangeStart
    property alias reloadGraphsButton: reloadGraphsButton
    anchors.fill: parent
    title: qsTr("Stall info")

    Frame {
        id: exportFilterFrame
        height: 90
        rightPadding: 12
        leftPadding: 12
        bottomPadding: 12
        topPadding: 12
        anchors.right: reloadGraphsButton.left
        anchors.rightMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.top: parent.top
        anchors.topMargin: 10

        Text {
            id: exportFilterLabels
            color: "#8b8b8b"
            text: qsTr("Data to export")
            anchors.top: parent.top
            anchors.topMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0
            font.pixelSize: 14
        }

        Row {
            id: row
            height: 40
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.top: exportFilterLabels.bottom
            anchors.topMargin: 5

            CheckBox {
                id: qtyBox
                text: qsTr("Quantity")
                checked: false
            }

            CheckBox {
                id: procBox
                text: qsTr("Process time")
                checked: false
            }

            CheckBox {
                id: respBox
                text: qsTr("Response time")
                checked: false
            }

            CheckBox {
                id: rejectBox
                text: qsTr("Rejected couints")
                checked: false
            }
        }
    }

    Button {
        id: reloadGraphsButton
        x: 996
        width: 150
        text: qsTr("Refresh graphs")
        anchors.bottom: exportFilterFrame.bottom
        anchors.bottomMargin: 0
        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.right: parent.right
        anchors.rightMargin: 10
    }

    Frame {
        id: dataRangeFrame
        height: 100
        anchors.right: advancedExportButton.left
        anchors.rightMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.top: exportFilterFrame.bottom
        anchors.topMargin: 10

        RangeSlider {
            id: dataRangeSlider
            anchors.rightMargin: 0
            anchors.leftMargin: 0
            anchors.bottomMargin: 0
            anchors.top: dataRangeLabel.bottom
            anchors.right: parent.right
            anchors.bottom: dataRangeStart.top
            anchors.left: parent.left
            anchors.topMargin: 0
            first.value: 0
            second.value: 1
        }

        Text {
            id: dataRangeLabel
            color: "#8b8b8b"
            text: qsTr("Data range")
            anchors.top: parent.top
            anchors.topMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0
            font.pixelSize: 14
        }

        Text {
            id: dataRangeStart
            text: qsTr("Text")
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            font.pixelSize: 14
        }

        Text {
            id: dataRangeEnd
            text: qsTr("Text")
            horizontalAlignment: Text.AlignRight
            anchors.right: parent.right
            anchors.rightMargin: 0
            font.pixelSize: 14
            anchors.bottomMargin: 0
            anchors.bottom: parent.bottom
        }
    }

    Button {
        id: advancedExportButton
        x: 996
        width: 150
        height: 50
        text: qsTr("Advanced export..")
        anchors.topMargin: 10
        anchors.top: reloadGraphsButton.bottom
        anchors.right: parent.right
        anchors.rightMargin: 10
    }

    ScrollView {
        id: scrollView
        anchors.bottomMargin: 15
        anchors.rightMargin: 10
        anchors.leftMargin: 10
        anchors.top: dataRangeFrame.bottom
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.topMargin: 10
        clip: true
        Column {
            width: parent.width
            Rectangle {
                id: qtyGraphBg
                width: parent.width
                height: 400
                border.color: "silver"
                border.width: 1
                QuantityBarGraph {
                    id: qtyGraph
                    anchors.fill: parent
                }
            }
            Rectangle {
                id: rejectGraphBg
                height: 400
                width: parent.width
                border.color: "silver"
                border.width: 1
                RejectedBarGraph {
                    id: rejectGraph
                    anchors.fill: parent
                }
            }
            Rectangle {
                id: timeGraphBg
                height: 400
                width: parent.width
                border.color: "silver"
                border.width: 1
                TimeLineGraph {
                    id: timeGraph
                    anchors.fill: parent
                }
            }
        }
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:1.25}D{i:2;anchors_x:20;anchors_y:"-6"}D{i:3;anchors_height:400;anchors_width:200}
D{i:14;anchors_y:112}
}
##^##*/

