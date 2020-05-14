import QtQuick 2.4
import "../"
MenuDelegateForm {
    itemImage.source: model.modelData.getImagePath(backend.getCurrentStallName())
    itemMouseArea.onClicked: {
        console.log(name)
        populateOrderPopup(itemName.text, "todo here", itemPrice.text, itemImage.source);
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
