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
        width = 320;
        playOnce = false;
        statusText.text = qsTr("Please wait...");
        statusImage.width = 180;
        statusImage.height = 180;
        statusImage.source = "assets/loader_animated.gif";
        statusImage.paused = false;
        modal = true;
        closePolicy = Popup.NoAutoClose;
    }

    function setAccepted(slip) {
        statusText.text = "Success! Your slip number is " + slip + ".";
        playOnce = true;
        statusImage.source = "assets/success.gif";
        statusImage.currentFrame = 3;
    }

    function setRejected() {
        statusText.text = "We're sorry. Your order was rejected.";
        statusImage.width = 50;
        statusImage.width = 50;
        statusImage.source = "assets/rejected.png";
    }

    function allowClose() {
        modal = false;
        closePolicy = Popup.CloseOnEscape | Popup.CloseOnPressOutside;
    }
}
