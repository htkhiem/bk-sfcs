import QtQuick 2.0
import "../delegates"
WaitlistForm {
    Component{
        id: waitlistview
        ListView {
            id: listView
            width: scrollView.width
            height: scrollView.height
            bottomMargin: 0
            model: waitlistViewModel
            delegate: OrderDelegate {
                width: listView.width
                itemImage.source: backend.getItemImagePath(backend.getCurrentStallIdx(), model.modelData.getFoodIdx())
                qtyNumber.text:  model.modelData.quantity
                nameText.text:  model.modelData.itemName
                priceText.text:  model.modelData.total
            }
        }

    }
}
