import QtQuick 2.4
import QtQuick.Controls 2.5

WaitingPopupForm {
    property bool playOnce: false
    enter: Transition {
        NumberAnimation {
            property: "opacity"
            from: 0
            to: 1
            duration: 200
        }
    }
    statusImage.onCurrentFrameChanged: {
        if (playOnce && statusImage.currentFrame === (statusImage.frameCount - 1)) {
            statusImage.paused = true;
        }
    }
    function setWaiting() {
        waitingPopup.width = 320;
        waitingPopup.playOnce = false;
        waitingPopup.statusText.text = qsTr("Please wait...");
        waitingPopup.statusImage.source = "assets/loader_animated.gif";
        waitingPopup.modal = true;
        waitingPopup.closePolicy = Popup.NoAutoClose;
    }

    function setAccepted(slip) {
        waitingPopup.statusText.text = "Success! Your slip number is " + slip + ".";
        waitingPopup.playOnce = true;
        waitingPopup.statusImage.source = "assets/success.gif";
    }

    function setRejected() {
        waitingPopup.statusText.text = "We're sorry. Your order was rejected.";
        waitingPopup.statusImage.source = "assets/rejected.png";
    }

    function allowClose() {
        waitingPopup.modal = false;
        waitingPopup.closePolicy = Popup.CloseOnEscape | Popup.CloseOnPressOutside;
    }
}
