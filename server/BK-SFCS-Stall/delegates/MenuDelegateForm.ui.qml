import QtQuick 2.4

Rectangle {
    id: rectangle
    width: 1280
    height: 100
    property alias itemName: itemName
    property alias itemDesc: itemDesc

    Image {
        id: itemImage
        width: 100
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.top: parent.top
        anchors.topMargin: 0
        fillMode: Image.PreserveAspectFit
        source: "qrc:/qtquickplugin/images/template_image.png"
    }

    Column {
        id: column
        spacing: 30
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.left: itemImage.right
        anchors.leftMargin: 10
        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10

        Text {
            id: itemName
            text: qsTr("Text")
            font.bold: true
            font.pixelSize: 20
        }

        Text {
            id: itemDesc
            text: qsTr("Text")
            font.pixelSize: 12
        }
    }
}

/*##^##
Designer {
    D{i:1;anchors_height:100;anchors_x:0;anchors_y:0}D{i:2;anchors_height:400;anchors_width:200;anchors_x:100;anchors_y:0}
}
##^##*/
s
