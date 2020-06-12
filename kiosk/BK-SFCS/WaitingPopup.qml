import QtQuick 2.4
import QtQuick.Controls 2.5
import QtGraphicalEffects 1.14

WaitingPopupForm {
    property int orderStatus: backend.currentOrderStatus;
    onOrderStatusChanged: {
        if (orderStatus == 1) { // order accepted
            waitingPopup.statusText.text = "Success! Your order is now being processed.";
            waitingPopup.statusImage.source = "assets/tick.png";
        }
        else if (orderStatus == 2) { // rejected
            waitingPopup.statusText.text = "The stall could not accept this order! Please try again later.";
            waitingPopup.statusImage.source = "./assets/forbidden.png";
        }
    }
}
