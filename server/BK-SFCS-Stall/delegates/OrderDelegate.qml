import QtQuick 2.4

OrderDelegateForm {

    stepButton.onClicked: {
        model.modelData.setAnswered(false);
        backend.setReply(orderID);
    }
    rejectButton.onClicked: {
        model.modelData.setAnswered(true)
        backend.setReply(orderID);
    }

}
