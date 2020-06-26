import QtQuick 2.4

OrderDelegateForm {

    property bool hold: false;

    stepButton.onActivated: {
           if (hold) backend.complete(index);

           else {
               timer.running = false;
               stepButton.text = "Finish";
               backend.hold(index);
               hold = true;

           };
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

       itemImage.source: backend.getItemImagePath(model.modelData.getFoodIdx())
}
