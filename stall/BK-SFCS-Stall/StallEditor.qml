import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Dialogs 1.3
import "./popups"
StallEditorForm {
    WaitingPopup {
        id: waitingPopup
        x: Math.round((parent.width - width) / 2)
        y: Math.round((parent.height - height) / 2)
    }

    Connections {
        target: backend
        function onManagementModeChanged() {
            checkAuthorization();
        }
        function onStallDataUpdateFinished() {
            waitingPopup.close();
        }
    }

    property bool needsToUpdateImage: false;
    function checkAuthorization() {
        if (backend.isManagementModeEnabled()) {
            state = "authorized"
            console.log("State changed")
        }
        else {
            authPswField.text = "";
            authPswField.placeholderText = "Wrong password"
        }
        waitingPopup.close();
    }

    function checkAndApplyEdits() {
        var valid = true;
        // If password is edited, make sure it matches the confirmation
        if (stallPswField.text != "") {
            if (stallPswField.text == stallPswConfField.text)
            backend.setStallPassword(stallPswField.text);
            else {
                valid = false;
                stallPswField.text = "";
                stallPswConfField.text = "";
                stallPswField.placeholderText = "Invalid stall password";
            }
        }
        if (stallMgmtPswField.text != "") {
            if (stallMgmtPswField.text == stallMgmtPswConfField.text)
                backend.setStallPassword(stallPswField.text)
            else {
                valid = false;
                stallMgmtPswField.text = "";
                stallMgmtPswConfField.text = "";
                stallMgmtPswField.placeholderText = "Invalid management password";
            }
        }
        if (!backend.setStallName(stallNameField.text)) {
            valid = false;
            stallNameField.text = "";
            stallNameField.placeholderText = "Invalid stall name";
        }
        return valid;
    }

    // Data initialisation code
    bigImage.source: backend.getCurrentStallImagePath()
    stallNameField.text: backend.getCurrentStallName()
    stallPswField.text: ""
    stallMgmtPswField.text: ""

    FileDialog {
        id: imageBrowser
        title: "Please choose an image for your stall"
        folder: shortcuts.home
        nameFilters: [ "Image files (*.jpg *.png)", "All files (*)" ]
        selectExisting: true
        selectFolder: false
        selectMultiple: false
        onAccepted: {
            console.log("You chose: " + imageBrowser.fileUrl)
            bigImage.source = imageBrowser.fileUrl;
            backend.setStallImage(imageBrowser.fileUrl);
            needsToUpdateImage = true;
            close()
        }
        onRejected: {
            console.log("Canceled")
            close()
        }
    }
    authorizeButton.onClicked: {
        waitingPopup.open();
        backend.loginAsManager(authPswField.text);
    }
    changeImageButton.onClicked: {
        imageBrowser.open();
    }
    confirmButton.onClicked: {
        if (checkAndApplyEdits()) {
            backend.updateStallData(needsToUpdateImage);
            waitingPopup.open();
            console.log("Stall data uploaded.");
        }
    }
}
