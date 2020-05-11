import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Dialogs 1.3

StallEditorForm {
    function authorize_editing(psw) {
        // placeholder for actual authorization code
        if (backend.loginAsManager(psw)) {
            state = "authorized"
            console.log("State changed")
        }
        else {
            authPswField.text = "";
            authPswField.placeholderText = "Wrong password"
        }
    }

    function check_edits() {
        // If password is edited, make sure it matches the confirmation
        if (stallPswField.text != "") {
            if (stallPswField.text == stallPswConfField.text)
                backend.setStallPassword(stallPswField.text)
        }
        if (stallMgmtPswField.text != "") {
            if (stallMgmtPswField.text == stallMgmtPswConfField.text)
                backend.setStallPassword(stallPswField.text)
        }
        if (!backend.setStallName(stallNameField.text))
            console.log("Empty name entered!") // TODO: actually notifying user of this error
        if (!backend.setStallImagePath(bigImage.source))
            console.log("Invalid path")

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
            close()
        }
        onRejected: {
            console.log("Canceled")
            close()
        }
    }
    authorizeButton.onClicked: authorize_editing(authPswField.text)
    changeImageButton.onClicked: {
        imageBrowser.open();
    }
    confirmButton.onClicked: {
        check_edits()
    }
}
