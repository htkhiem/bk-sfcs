import QtQuick 2.4

Rectangle {
    id: itemBg
    width: 200
    height: 328
    color: "#c8c8c8"
    property alias itemPrice: itemPrice
    property alias itemMouseArea: itemMouseArea
    property alias itemImage: itemImage
    property alias itemName: itemName

    Text {
        id: itemName
        x: 85
        anchors.horizontalCenterOffset: 1
        anchors.top: itemImage.bottom
        anchors.topMargin: 28
        anchors.horizontalCenter: parent.horizontalCenter
        horizontalAlignment: Text.AlignHCenter
        font.bold: false
        font.pixelSize: 14
    }

    Image {
        id: itemImage
        x: 0
        width: 200
        height: 200
        anchors.top: parent.top
        anchors.topMargin: 0
        source: "qrc:/qtquickplugin/images/template_image.png"
        fillMode: Image.PreserveAspectFit
    }

    Text {
        id: itemPrice
        x: 79
        y: 295
        color: "#2b6b20"
        text: qsTr("Text")
        font.bold: true
        horizontalAlignment: Text.AlignRight
        anchors.right: parent.right
        anchors.rightMargin: 18
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 18
        font.pixelSize: 16
    }

    MouseArea {
        id: itemMouseArea
        x: 79
        y: 295
        anchors.fill: parent
    }
}

/*##^##
Designer {
    D{i:2;anchors_y:0}
}
##^##*/
