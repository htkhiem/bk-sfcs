import QtQuick 2.12
import QtQuick.Controls 2.5
import "../delegates"

Page {
    id: page
    width: 1280
    height: 720
    anchors.fill: parent
    title: qsTr("Waitlist")
    ScrollView {
        id: scrollView
        anchors.fill: parent
        clip: true
        ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
        ScrollBar.vertical.policy: ScrollBar.AlwaysOn

        ListView {
            id: listView
            width: scrollView.width
            height: scrollView.height
            bottomMargin: 0
            model: ListModel {
                ListElement {
                    image: "placeholders/200.png"
                    qty: 1
                    name: "Item name here"
                    desc: "Some descriptions about this item."
                    price: 10000
                    isOOS: false
                }
                ListElement {
                    image: "placeholders/200.png"
                    qty: 5
                    name: "Another item"
                    desc: "Another meaningless description."
                    price: 15000
                    isOOS: true
                }
            }
            delegate: OrderDelegate {
                width: listView.width
                itemImage.source: image
                qtyNumber.text: qty
                nameText.text: name
                priceText.text: price
            }
        }
    }
}



