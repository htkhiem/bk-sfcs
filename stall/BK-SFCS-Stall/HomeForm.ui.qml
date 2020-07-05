import QtQuick 2.12
import QtQuick.Controls 2.5

Page {
    id: page
    width: 1280
    height: 720
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
                    name: "Daily sales (1 week)"
                    checked: true
                }
                ListElement {
                    name: "Monthly sales (3D weeks)"
                    checked: true
                }
                ListElement {
                    name: "Daily average response delay"
                    checked: true
                }
                ListElement {
                    name: "Weekly item market share"
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
            anchors.bottomMargin: 0
            anchors.top: dataRangeLabel.bottom
            anchors.right: parent.right
            anchors.bottom: dataRangeStart.top
            anchors.left: parent.left
            anchors.topMargin: 0
            first.value: 0.25
            second.value: 0.75
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

        GridView {
            id: gridView
            x: 10
            y: 180
            width: 1260
            height: 525
            cellWidth: width / 2
            cellHeight: height / 2
            model: ListModel {
                ListElement {
                    name: "Grey"
                    colorCode: "grey"
                }

                ListElement {
                    name: "Red"
                    colorCode: "red"
                }

                ListElement {
                    name: "Blue"
                    colorCode: "blue"
                }

                ListElement {
                    name: "Green"
                    colorCode: "green"
                }
            }
            delegate: Item {
                x: 5
                height: 50
                Column {
                    Rectangle {
                        width: 40
                        height: 40
                        color: colorCode
                        anchors.horizontalCenter: parent.horizontalCenter
                    }

                    Text {
                        x: 5
                        text: name
                        anchors.horizontalCenter: parent.horizontalCenter
                        font.bold: true
                    }
                    spacing: 5
                }
            }
        }
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.75}D{i:2;anchors_height:160;anchors_width:110}D{i:1;anchors_width:200;anchors_x:8;anchors_y:10}
D{i:9;anchors_y:112}D{i:11;anchors_height:40;anchors_width:205;anchors_x:"-58";anchors_y:304}
D{i:10;anchors_width:1260;anchors_x:10;anchors_y:66}D{i:15;anchors_y:112}D{i:16;anchors_y:112}
D{i:18;anchors_height:140;anchors_width:140;anchors_x:10;anchors_y:182}D{i:17;anchors_height:200;anchors_width:200;anchors_x:0;anchors_y:249}
}
##^##*/

