import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.11
import QtGraphicalEffects 1.14
import QtTest 1.14

MainForm {
    property bool isSearching: false
    backButton.onClicked: {
        if (isSearching) {
            isSearching = false;
            backend.searchFilter(); // Only filter by category now
        } else {
            homeFormLoader.source = "HomeForm.ui.qml"
            stallLoadWait.wait(300)
            stackView.pop()
            stallMenuLoader.sourceComponent = undefined;
        }
    }
    backButton.visible: (stackView.depth > 1 && isReady()) ? true : false
    searchButton.onClicked: {
        blurUnfocused()
        searchPopup.open()
    }
    Loader {
        id: homeFormLoader
        sourceComponent: homeMenu
    } 
    Component {
        id: homeMenu
        HomeForm {
        }
    }
    Loader {
        id: stallMenuLoader
    }
    Component {
        id: stallMenu
        StallMenu {
        }
    }
    SearchPopup {
        x: Math.round((parent.width - width) / 2)
        y: Math.round((parent.height - height) / 2)
        id: searchPopup
        onOpened: isSearching = true;
        searchButton.onClicked:{
            searchMenu();
            close();
        }
        onClosed: refocus();
    }

    // Signal spies to wait for signals before doing stuff

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

    function searchMenu() {
        if (isSearching) {
            // Search by both name and category
            backend.searchFilter(searchPopup.searchField.text);
        }
        else // Search only by category
            backend.searchFilter();
    }

    function openMenu(stallIdx) {
        backend.setCurrentStallIdx(stallIdx);
        backend.getStallMenu(stallIdx); // load menu
        stallMenuLoader.sourceComponent = stallMenu;
        stallMenuLoader.item.title = backend.getCurrentStallName();
        stallMenuLoader.item.pageBg.source = backend.getCurrentStallImagePath();
        stackView.push(stallMenuLoader);
        homeFormLoader.sourceComponent = undefined; // unload stall list
        console.log(stackView.depth);
    }
}
