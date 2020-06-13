import QtQuick 2.4

OrderDelegateForm {
    stepButton.onClicked: {
           backend.hold(index);
       }
       rejectButton.onClicked: {
           backend.reject(index);
       }
    itemImage.source: backend.getItemImagePath(backend.getCurrentStallIdx(), model.modelData.getFoodIdx())
}
