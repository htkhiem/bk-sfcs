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
            model: waitlistViewModel
            delegate: OrderDelegate {
                width: listView.width
                qtyNumber.text: model.modelData.quantity
                nameText.text: model.modelData.itemName
                priceText.text: model.modelData.total
                hold: accepted
            }
        }
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.75}
}
##^##*/

