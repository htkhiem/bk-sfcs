import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.11
import QtGraphicalEffects 1.14
import QtTest 1.14

MainForm {
    property bool isSearching: false
    backButton.onClicked: {
        if (isSearching) {
            backend.populateMenuViewModel()
            isSearching = false
        } else {
            homeFormLoader.source = "HomeForm.ui.qml"
            stallLoadWait.wait(300)
            stackView.pop()
            stallMenuLoader.source = ""
        }
    }
    searchButton.onClicked: {
        blurUnfocused()
        searchPopup.open()
    }
    Loader {
        id: homeFormLoader
        source: "HomeForm.ui.qml"
    }
    Loader {
        id: stallMenuLoader
    }
    SearchPopup {
        x: Math.round((parent.width - width) / 2)
        y: Math.round((parent.height - height) / 2)
        id: searchPopup
        onOpened: isSearching = true;
    }
    FastBlur {
        id: bgBlur
        anchors.fill: parent
        source: parent
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
    // Signal spies to wait for signals before doing stuff
    SignalSpy {
        id: fadeOutWait
        target: opacityFade
        signalName: "finished"
    }
    SignalSpy {
        id: menuLoadWait
        target: stallMenuLoader
        signalName: "loaded"
    }
    SignalSpy {
        id: stallLoadWait
        target: homeFormLoader
        signalName: "loaded"
    }

    function openMenu(stallIdx) {
        backend.setCurrentStall(stallIdx);
        backend.populateMenuViewModel(); // load menu
        stallMenuLoader.source = "StallMenu.qml"
        stackView.push(stallMenuLoader)
        menuLoadWait.wait(300);
        stallMenuLoader.item.title = backend.getCurrentStallName();
        homeFormLoader.source = ""; // unload stall list
        console.log(stackView.depth)
    }

    function blurUnfocused() {
        bgBlur.visible = true;
        bgBlur.opacity = 1;
    }
    function refocus() {
        bgBlur.opacity = 0;
        fadeOutWait.wait(1000);
        bgBlur.visible = false;
    }
}
