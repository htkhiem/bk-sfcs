import QtQuick 2.4
import QtQuick.Controls 2.12

Rectangle {
    id: bg
    width: 1280
    height: 220
    property alias categoryBox: categoryBox
    property alias itemImage: itemImage
    property alias bg: bg
    property alias removeButton: removeButton
    property alias priceField: priceField
    property alias oosCheckbox: oosCheckbox
    property alias estTimeField: estTimeField
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
        enabled: false
        text: qsTr("Change")
        anchors.right: descField.left
        anchors.rightMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.top: itemImage.bottom
        anchors.topMargin: 10
    }

    TextField {
        enabled: false
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
        enabled: false
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
        enabled: false
        id: priceField
        anchors.left: oosCheckbox.left
        anchors.leftMargin: 0
        font.bold: true
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.top: parent.top
        anchors.topMargin: 10
        placeholderText: qsTr("Price")
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
        enabled: false
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
        enabled: false
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
        enabled: false
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
    D{i:0;formeditorZoom:0.6600000262260437}
}
##^##*/

