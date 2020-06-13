import QtQuick 2.4

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
}
