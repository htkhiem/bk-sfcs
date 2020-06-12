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
        x: Math.round((parent.width - width) / 2)
        y: Math.round((parent.height - height) / 2)
        id: waitingPopup
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

    function sendOrder() {
        orderPopup.close();
        backend.sendOrder();
        waitingPopup.statusText.text = tr("Please wait...");
        waitingPopup.statusImage.source = "assets/loader.png";
        waitingPopup.open();
    }
}
