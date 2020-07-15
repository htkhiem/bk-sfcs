import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import "./popups"

MainForm {
    property bool promptConfirmExit: false
    DisconnectPopup {
        id: disconnectPopup
        x: Math.round((parent.width - width) / 2)
        y: Math.round((parent.height - height) / 2)
    }
    UnsavedChangesPopup {
        id: unsavedChangesPopup
        x: Math.round((parent.width - width) / 2)
        y: Math.round((parent.height - height) / 2)
    }

    Connections {
        target: backend
        function onConnectionLost() {
            disconnectPopup.open(); // No way to turn off except restart
        }
    }
    function activateConfirmExit() {
        promptConfirmExit = true;
    }
    function deactivateConfirmExit() {
        promptConfirmExit = false;
    }
    function load(path) {
        tabLoader.source = path;
    }

    salesTabButton.onClicked: {
        if (promptConfirmExit) {
            unsavedChangesPopup.nextPath = "Home.qml";
            unsavedChangesPopup.open();
        }
        else load("Home.qml")
    }

    waitlistTabButton.onClicked: {
        if (promptConfirmExit) {
            unsavedChangesPopup.nextPath = "order_process/WaitList.qml";
            unsavedChangesPopup.open();
        }
        else load("order_process/WaitList.qml")
    }
    menuEditorTabButton.onClicked: {
        if (promptConfirmExit) {
            unsavedChangesPopup.nextPath = "menu_editor/MenuEditor.qml";
            unsavedChangesPopup.open();
        }
        else load("menu_editor/MenuEditor.qml")
    }
    stallEditorTabButton.onClicked: {
        if (promptConfirmExit) {
            unsavedChangesPopup.nextPath = "StallEditor.qml";
            unsavedChangesPopup.open();
        }
        else load("StallEditor.qml")
    }
}
