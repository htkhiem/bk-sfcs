import QtQuick 2.0
import QtQuick.Controls 2.5
import QtGraphicalEffects 1.12
StallMenuForm {
    Connections {
        target: backend
        function onCurrentOrderStatusChanged(slip) {
            waitingPopup.width = 640;
            if (slip !== -1) { // accepted
                waitingPopup.setAccepted(slip);
            }
            else { // rejected
                waitingPopup.setRejected();
            }
            waitingPopup.allowClose();
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
        backend.getFullResItemImage(idx);
        orderPopup.image.source = backend.getItemImagePath(idx);
        orderPopup.orderButton.text = price + " VND\nORDER";
        blurUnfocused();
        backend.initOrder(idx);
        orderPopup.open();
    }

    function sendOrder() {
        orderPopup.close();
        backend.sendOrder();
        waitingPopup.setWaiting();
        waitingPopup.open();
    }
}
