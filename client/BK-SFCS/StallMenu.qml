import QtQuick 2.0
import QtGraphicalEffects 1.12
StallMenuForm {
    pageBg.source: backend.getCurrentStallImagePath();
    OrderPopup {
        x: Math.round((parent.width - width) / 2)
        y: Math.round((parent.height - height) / 2)
        id: orderPopup
    }
    WaitingPopup {
        id: waitingPopup
        x: Math.round((parent.width - width) / 2)
        y: Math.round((parent.height - height) / 2)
    }
    function populateOrderPopup(name, desc, time, price, imgPath) {
        orderPopup.name.text = name;
        orderPopup.desc.text = desc;
        orderPopup.estTime.text = qsTr("Estimated waiting time: ") + time + qsTr(" minutes");
        orderPopup.price = parseFloat(price);
        orderPopup.quantitySelector.currentIndex = 0;
        orderPopup.orderButton.text = price + " VND\nORDER";
        orderPopup.image.source = imgPath;
        blurUnfocused();
        orderPopup.open();
    }
    function waitForOrderResponse(name) {
        waitingPopup.statusText.text = "Your order has been sent. Please wait...";
        waitingPopup.statusImage.source = "assets/loader.png";
        waitingPopup.open();
        var orderResult = backend.waitForResults(name);
        if (orderResult) { // succeeded
            waitingPopup.statusText.text = "Succeeded! Your order is now being processed.";
            waitingPopup.statusImage.source = "assets/tick.png";
        }
        else {
            waitingPopup.statusText.text = "The stall could not accept this order! Please try again later.";
            waitingPopup.statusImage.source = "./assets/forbidden.png";
        }
    }
}
