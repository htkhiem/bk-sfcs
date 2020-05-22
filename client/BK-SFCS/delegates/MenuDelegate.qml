import QtQuick 2.4
import "../"
MenuDelegateForm {
    itemImage.source: model.modelData.getImagePath(backend.getCurrentStallName())
    itemMouseArea.onClicked: {
        backend.setOrderFoodItem(index);
        console.log(name)
        populateOrderPopup(itemName.text, model.modelData.description, model.modelData.estimatedTime, itemPrice.text, itemImage.source);
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
