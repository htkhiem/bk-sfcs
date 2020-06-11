import QtQuick 2.4

OrderDelegateForm {

    stepButton.onClicked: {
        model.modelData.setAnswered(false);
        backend.setReply(model.modelData.orderID);
    }
    rejectButton.onClicked: {
        model.modelData.setAnswered(true);
        backend.setReply(model.modelData.orderID);
    }

}
