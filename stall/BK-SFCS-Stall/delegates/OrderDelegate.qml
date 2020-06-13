import QtQuick 2.4

OrderDelegateForm {
    stepButton.onClicked: {
           model.modelData.setAnswered(false);
           backend.hold(model.modeldata.orderID);
       }
       rejectButton.onClicked: {
           model.modelData.setAnswered(true);
           backend.reject(model.modeldata.orderID);
       }
}
