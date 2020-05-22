import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.11
import QtGraphicalEffects 1.14
import QtTest 1.14

ApplicationWindow {
    property bool ready: true;
    id: window
    visible: true
    width: 1280
    height: 720
    title: qsTr("Smart Food Court System")
    Main {
        id: navLayout
    }
    FastBlur {
        id: totalBlur
        anchors.fill: parent
        source: navLayout
        radius: 32
        visible: false
        opacity: 0
        Behavior on opacity {
            NumberAnimation {
                id: opacityFade
                duration: 200
            }
        }
    }
    function blurUnfocused() {

        totalBlur.visible = true;
        ready = false;
        totalBlur.opacity = 1;
        ready = true;
    }
    function refocus() {
        ready = false;
        totalBlur.opacity = 0;
        ready = true;
        totalBlur.visible = false;
    }
    function isReady() { // dirty mutex-esque function
        return ready;
    }
}
