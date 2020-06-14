import QtQuick 2.0
import QtQuick.Controls 2.5
import QtGraphicalEffects 1.12
StallMenuForm {
    Connections {
        target: backend
        function onCurrentOrderStatusChanged(slip) {
            waitingPopup.width = 640;
            if (slip !== -1) { // accepted
                waitingPopup.statusText.text = "Success! Your slip number is " + slip + ".";
                waitingPopup.playOnce = true;
                waitingPopup.statusImage.source = "assets/success2.gif";
            }
            else { // rejected
                waitingPopup.statusText.text = "We're sorry. Your order was rejected.";
                waitingPopup.statusImage.source = "assets/forbidden.png";
            }
            waitingPopup.modal = false;
            waitingPopup.closePolicy = Popup.CloseOnEscape | Popup.CloseOnPressOutside;
        }
    }

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

    function populateOrderPopup(name, desc, time, price, idx) {
        orderPopup.name.text = name;
        orderPopup.desc.text = desc;
        orderPopup.estTime.text = qsTr("Estimated waiting time: ") + time + qsTr(" minutes");
        orderPopup.price = parseFloat(price);
        orderPopup.quantitySelector.currentIndex = 0;
        orderPopup.image.source = backend.getItemImagePath(idx);
        orderPopup.orderButton.text = price + " VND\nORDER";
        blurUnfocused();
        backend.initOrder(idx);
        orderPopup.open();
    }


    function sendOrder() {
        orderPopup.close();
        backend.sendOrder();
        waitingPopup.width = 320;
        waitingPopup.playOnce = false;
        waitingPopup.statusText.text = qsTr("Please wait...");
        waitingPopup.statusImage.source = "assets/loader_animated.gif";
        waitingPopup.modal = true;
        waitingPopup.closePolicy = Popup.NoAutoClose;
        waitingPopup.open();
    }
}
