import QtQuick 2.4
import QtQuick.Controls 2.12

Rectangle {
    id: bg
    width: 1280
    height: 220
    property alias estTimeField: estTimeField
    property alias categoryBox: categoryBox
    property alias itemImage: itemImage
    property alias bg: bg
    property alias removeButton: removeButton
    property alias priceField: priceField
    property alias oosCheckbox: oosCheckbox
    border.color: "#8a8a8a"
    border.width: 1
    property alias descField: descField
    property alias nameField: nameField
    property alias changeImageButton: changeImageButton

    Image {
        id: itemImage
        width: 100
        height: 100
        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 10
        fillMode: Image.PreserveAspectFit
        source: "qrc:/qtquickplugin/images/template_image.png"
    }

    Button {
        id: changeImageButton
        text: qsTr("Change")
        anchors.right: descField.left
        anchors.rightMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.top: itemImage.bottom
        anchors.topMargin: 10
    }

    TextField {
        id: nameField
        text: ""
        anchors.right: priceField.left
        anchors.rightMargin: 10
        font.bold: true
        anchors.left: itemImage.right
        anchors.leftMargin: 10
        anchors.top: parent.top
        anchors.topMargin: 10
        placeholderText: qsTr("Item name")
    }

    TextField {
        id: descField
        anchors.right: priceField.left
        anchors.rightMargin: 10
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        anchors.left: itemImage.right
        anchors.leftMargin: 10
        anchors.top: nameField.bottom
        anchors.topMargin: 10
        placeholderText: qsTr("Item description")
    }

    TextField {
        id: priceField
        placeholderText: "Price in VND"
        anchors.left: oosCheckbox.left
        anchors.leftMargin: 0
        font.bold: true
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.top: parent.top
        anchors.topMargin: 10
    }

    CheckBox {
        id: oosCheckbox
        x: 1032
        text: qsTr("Out of stock")
        anchors.top: estTimeField.bottom
        anchors.topMargin: 70
        anchors.right: removeButton.left
        anchors.rightMargin: 6
    }

    DelayButton {
        id: removeButton
        x: 1170
        y: 132
        text: qsTr("Remove item")
        delay: 1000
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
    }

    TextField {
        id: estTimeField
        anchors.left: oosCheckbox.left
        anchors.leftMargin: 0
        placeholderText: qsTr("Estimated time in minutes")
        anchors.top: priceField.bottom
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.topMargin: 10
        font.bold: true
    }

    ComboBox {
        id: categoryBox
        textRole: "name"
        model: categoryViewModel
        anchors.top: estTimeField.bottom
        anchors.topMargin: 10
        anchors.left: oosCheckbox.left
        anchors.leftMargin: 0
        anchors.right: parent.right
        anchors.rightMargin: 10
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.6600000262260437}D{i:2;anchors_x:15;anchors_y:177}D{i:3;anchors_x:304;anchors_y:60}
D{i:4;anchors_x:304;anchors_y:112}D{i:5;anchors_width:350;anchors_x:968;anchors_y:25}
D{i:6;anchors_y:56}D{i:7;anchors_y:56}D{i:8;anchors_width:350;anchors_x:1072;anchors_y:25}
D{i:9;anchors_width:350;anchors_x:1130;anchors_y:106}
}
##^##*/

