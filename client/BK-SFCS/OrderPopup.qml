import QtQuick 2.4

OrderPopupForm {
    property int price;
    closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside
    quantitySelector.onCurrentIndexChanged: {
        orderButton.text = orderPopup.price * (quantitySelector.currentIndex + 1) + qsTr("VND\nORDER")
    }
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
