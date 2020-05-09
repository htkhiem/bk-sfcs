import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Dialogs 1.3

StallEditorForm {
    function authorize_editing(psw) {
        // placeholder for actual authorization code
        if (psw === "root") {
            state = "authorized"
            console.log("State changed")
        }
        else {
            authPswField.text = "";
            authPswField.placeholderText = "Wrong password"
        }
    }
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
}
