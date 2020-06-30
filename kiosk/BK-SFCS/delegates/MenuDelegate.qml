import QtQuick 2.4
import "../"
MenuDelegateForm {
    property bool matching: true
    property bool oos: false
    property int foodIdx
    Connections {
        target: backend
        function onItemImageChanged(sidx, midx) {
            // only update if it is the one and also currently visible on screen
            if (sidx === backend.getCurrentStallIdx() && midx === index)
                itemImage.source = backend.getItemImagePath(midx);
        }
    }
    Component.onCompleted: {
        itemImage.source = backend.getItemImagePath(index);
    }

    onOosChanged: {
        if (oos) state = "oos";
        else state = matching? "base" : "hidden";
    }

    onMatchingChanged: {
        if (!oos) {
            if (matching) {
                state = "base";
            }
            else {
                state = "hidden"
            }
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
