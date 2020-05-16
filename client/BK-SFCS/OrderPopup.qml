import QtQuick 2.4
import QtQuick.Controls 2.5
import QtGraphicalEffects 1.14

OrderPopupForm {
    property int price;
    closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside
    quantitySelector.onCurrentIndexChanged: {
        orderButton.text = price * (quantitySelector.currentIndex + 1) + qsTr(" VND\nORDER")
        backend.setOrderQuantity(quantitySelector.currentIndex + 1);
    }
    orderButton.onActivated: backend.sendOrder();

    enter: Transition {
        NumberAnimation {
            property: "opacity"
            from: 0
            to: 1
            duration: 200
        }
    }
    exit: Transition {
        NumberAnimation {
            property: "opacity"
            from: 1
            to: 0
            duration: 100
        }
    }    
}
