import QtQuick 2.12
import QtQuick.Controls 2.5
import "./delegates"

Page {
    id: page
    width: 1280
    height: 720
    property alias timeGraph: timeGraph
    property alias rejectGraph: rejectGraph
    property alias qtyGraph: qtyGraph
    property alias dataRangeEnd: dataRangeEnd
    property alias dataRangeStart: dataRangeStart
    property alias reloadGraphsButton: reloadGraphsButton
    anchors.fill: parent
    title: qsTr("Stall info")

    Frame {
        id: vizFilterFrame
        height: 50
        rightPadding: 2
        leftPadding: 2
        bottomPadding: 2
        topPadding: 2
        anchors.right: reloadGraphsButton.left
        anchors.rightMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.top: parent.top
        anchors.topMargin: 10

        ListView {
            id: vizCheckboxesList
            orientation: ListView.Horizontal
            anchors.fill: parent
            flickableDirection: Flickable.HorizontalFlick
            model: ListModel {
                ListElement {
                    name: "Quantity"
                    checked: true
                }
                ListElement {
                    name: "Response and processing time"
                    checked: true
                }
                ListElement {
                    name: "Rejected orders"
                    checked: true
                }
            }
            delegate: CheckBox {
                text: name
                checked: checked
            }
        }
    }

    Button {
        id: reloadGraphsButton
        x: 996
        width: 150
        text: qsTr("Refresh graphs")
        anchors.bottom: vizFilterFrame.bottom
        anchors.bottomMargin: 0
        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.right: parent.right
        anchors.rightMargin: 10
    }

    Frame {
        id: dataRangeFrame
        height: 100
        anchors.right: graphExportButton.left
        anchors.rightMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.top: vizFilterFrame.bottom
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
        id: graphExportButton
        x: 996
        width: 150
        height: dataRangeFrame.height / 2 - 5
        text: qsTr("Export graph")
        font.bold: true
        anchors.top: dataRangeFrame.top
        anchors.topMargin: 0
        anchors.rightMargin: 10
        anchors.right: parent.right
    }

    Button {
        id: advancedExportButton
        x: 996
        y: 112
        width: 150
        height: graphExportButton.height
        text: qsTr("Advanced export..")
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.bottom: dataRangeFrame.bottom
        anchors.bottomMargin: 0
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
