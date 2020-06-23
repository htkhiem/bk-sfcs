import QtQuick 2.4

OrderDelegateForm {
    stepButton.onClicked: {
           backend.hold(index);
       }
       rejectButton.onClicked: {
           backend.reject(index);
       }
       Timer {
           id: timer
           interval: 15000
           running: true
           repeat: false
           onTriggered: {
               backend.reject(index)
           }
       }

    itemImage.source: backend.getItemImagePath(backend.getCurrentStallIdx(), model.modelData.getFoodIdx())
}
