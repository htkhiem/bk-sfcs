import QtQuick 2.4

OrderDelegateForm {

    property bool hold: false;

    onHoldChanged: {
        if (hold) {
            setHeld();
        }
    }

    stepButton.onActivated: {
        if (hold) backend.complete(index);
        else {
            setHeld();
            hold = true;
            backend.hold(index);
        }
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
    function setHeld() {
        timer.running = false;
        stepButton.text = "Finish";
        stepButton.progress = 0;
        rejectButton.enabled = false;
    }

    itemImage.source: backend.getItemImagePath(model.modelData.getFoodIdx())
}
