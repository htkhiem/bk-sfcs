import QtQuick 2.0
import "./delegates"

ListView {
    id: listView
    width: parent.width
    height: parent.height
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
