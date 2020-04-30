import QtQuick 2.12
import QtQuick.Controls 2.5
import "./delegates"

Page {
    id: page
    width: 1280
    height: 720
    property alias revertButton: revertButton
    property alias confirmButton: confirmButton
    anchors.fill: parent

    title: qsTr("Menu Editor")

    ScrollView {
        id: scrollView
        anchors.bottomMargin: 10
        clip: true
        anchors.top: instr.bottom
        ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
        ScrollBar.vertical.policy: ScrollBar.AlwaysOn
        anchors.right: parent.right
        anchors.bottom: confirmButton.top
        anchors.left: parent.left
        anchors.topMargin: 10

        ListView {
            id: listView
            width: scrollView.width
            height: 160
            bottomMargin: 0
            model: ListModel {
                ListElement {
                    image: "placeholders/200.png"
                    name: "Item name here"
                    desc: "Some descriptions about this item."
                    price: 10000
                    isOOS: false
                }
                ListElement {
                    image: "placeholders/200.png"
                    name: "Another item"
                    desc: "Another meaningless description."
                    price: 15000
                    isOOS: true
                }
            }
            delegate: MenuDelegate {
                width: listView.width
                itemImage.source: image
                nameField.text: name
                descField.text: desc
                priceField.text: price + qsTr("VND")
                oosCheckbox.checked: isOOS
            }
        }
    }

    Text {
        id: instr
        text: qsTr("Select a food item to edit its information (price, description, image, etc.)")
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.top: parent.top
        anchors.topMargin: 10
        font.pixelSize: 14
    }

    DelayButton {
        id: confirmButton
        y: 673
        text: qsTr("Confirm change proposal")
        enabled: false
        delay: 5000
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.left: revertButton.right
        anchors.leftMargin: 10
    }

    DelayButton {
        id: revertButton
        y: 570
        width: 240
        text: qsTr("Revert")
        anchors.left: parent.left
        anchors.bottomMargin: 10
        anchors.bottom: parent.bottom
        anchors.leftMargin: 10
        enabled: false
        delay: 5000
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.5}D{i:8;anchors_x:589}
}
##^##*/

