import QtQuick 2.4
import QtQuick.Controls 2.5

Popup {
    id: popup
    property alias name: name
    width: 670
    height: 670
    rightPadding: 0
    leftPadding: 0
    bottomPadding: 0
    topPadding: 0
    padding: 0
    margins: 0
    rightMargin: 0
    leftMargin: 0
    bottomMargin: 0
    topMargin: 0
    property alias orderButton: orderButton
    property alias quantitySelector: quantitySelector
    property alias image: image

    Rectangle {
        id: popupBg
        color: "#00000000"
        anchors.fill: parent

        DelayButton {
            id: orderButton
            y: 0
            height: 170
            text: qsTr("Order")
            font.bold: true
            font.pointSize: 12
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.left: infoBg.right
            anchors.leftMargin: 0
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
        }

        Tumbler {
            id: quantitySelector
            anchors.bottom: orderButton.top
            anchors.bottomMargin: 0
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 0
            anchors.left: image.right
            anchors.leftMargin: 0
            font.pointSize: 18
            font.bold: false
            wheelEnabled: false
            visible: true
            model: [1, 2, 3, 4, 5]
        }

        Rectangle {
            id: infoBg
            y: 500
            width: 500
            color: "#000000"
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.top: image.bottom
            anchors.topMargin: 0

            Text {
                id: name
                x: 311
                y: -476
                color: "#ffffff"
                text: qsTr("Text")
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: parent.top
                anchors.topMargin: 24
                font.pixelSize: 24
            }
        }

        Image {
            id: image
            width: 500
            height: 500
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 0
            fillMode: Image.PreserveAspectFit
            source: "qrc:/qtquickplugin/images/template_image.png"
        }
    }
}

/*##^##
Designer {
    D{i:2;anchors_width:170;anchors_x:500}D{i:3;anchors_height:250;anchors_width:80;anchors_x:0;anchors_y:500}
D{i:4;anchors_height:400;anchors_width:200;anchors_x:0}D{i:1;anchors_height:200;anchors_width:200}
}
##^##*/

