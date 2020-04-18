import QtQuick 2.4
import "../"
MenuDelegateForm {
    OrderPopup {
        x: Math.round((parent.width - width) / 2)
        y: Math.round((parent.height - height) / 2)
        id: orderPopup
        name.text: itemName.text
        image.source: itemImage.source

    }

    itemMouseArea.onClicked: {
        console.log(name)
        orderPopup.price = parseInt(itemPrice.text)
        orderPopup.orderButton.text = orderPopup.price + qsTr("VND\nORDER")
        orderPopup.open();
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
