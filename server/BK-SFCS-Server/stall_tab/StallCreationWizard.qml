import QtQuick 2.4
import QtQuick.Dialogs 1.3

StallCreationWizardForm {
    finishButton.onClicked: {
        // Check if any is empty
        if (nameField.text == "") {
            nameField.placeholderText = qsTr("Please enter a name! (max. 32 characters)");
        }
        else if (pswField.text == "") {
            pswField.placeholderText = qsTr("Please enter a login password!");
        }
        else if (mgrPswField.text == "") {
            mgrPswField.placeholderText = qsTr("Please enter a management password!");
        }
        else if (image.source == "") {
            changeImageButton.text = "There must be an image or logo!";
        }
        else {
            server.createNewStall(nameField.text, imageBrowser.fileUrl, pswField.text, mgrPswField.text);
            popup.close();
        }
    }
    changeImageButton.onClicked: imageBrowser.open();
    FileDialog {
        id: imageBrowser
        title: "Please choose an image for the new stall"
        folder: shortcuts.home
        nameFilters: [ "Image files (*.jpg *.png)", "All files (*)" ]
        selectExisting: true
        selectFolder: false
        selectMultiple: false
        onAccepted: {
            console.log("You chose: " + imageBrowser.fileUrl)
            image.source = imageBrowser.fileUrl;
            close()
        }
        onRejected: {
            console.log("Canceled")
            close()
        }
    }
}
