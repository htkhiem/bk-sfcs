import QtQuick 2.4
import "../"
MenuDelegateForm {
    Connections {
        target: backend
        function onItemImageChanged(sidx, midx) {
            // only update if it is the one and also currently visible on screen
            if (sidx === backend.getCurrentStallIdx() && midx === index)
                itemImage.source = backend.getItemImagePath(midx);
        }
    }

    itemMouseArea.onClicked: {
        console.log(index)
        backend.setOrderFoodItem(index);
        console.log(name)
        populateOrderPopup(itemName.text, model.modelData.description, model.modelData.estimatedTime, itemPrice.text, index);
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
