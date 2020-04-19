import QtQuick 2.4

OrderPopupForm {
    property int price;
    closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside
    quantitySelector.onCurrentIndexChanged: {
        orderButton.text = orderPopup.price * (quantitySelector.currentIndex + 1) + qsTr("VND\nORDER")
    }
}
