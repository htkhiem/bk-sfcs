import QtQuick 2.4
import QtQuick.Controls 2.5
import QtGraphicalEffects 1.14

OrderPopupForm {
    property int price;
    property int index;
    Connections {
        target: backend
        function onItemImageChanged(sidx, midx) {
            image.source = backend.getItemImagePath(midx);
        }
        function onMenuJsonUpdated() {
            if (menuViewModel[orderPopup.index].isOOS === true) close();
        }
    }
    onClosed: refocus(); // stop blurring background
    quantitySelector.onCurrentIndexChanged: {
        orderButton.text = price * (quantitySelector.currentIndex + 1) + qsTr(" VND\nORDER")
        backend.setOrderQuantity(quantitySelector.currentIndex + 1);
    }
    orderButton.onActivated: {
        sendOrder();
    }
    enter: Transition {
        NumberAnimation {
            property: "opacity"
            from: 0
            to: 1
            duration: 200
        }
    }
}
