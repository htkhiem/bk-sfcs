import QtQuick 2.0
import QtGraphicalEffects 1.12
StallMenuForm {
    OrderPopup {
        x: Math.round((parent.width - width) / 2)
        y: Math.round((parent.height - height) / 2)
        id: orderPopup
        onClosed: refocus(); // stop blurring background
    }
    function populateOrderPopup(name, desc, price, imgPath) {
        orderPopup.name.text = name;
        orderPopup.price = price;
        orderPopup.image.source = imgPath;
        blurUnfocused();
        orderPopup.open();
    }
}
