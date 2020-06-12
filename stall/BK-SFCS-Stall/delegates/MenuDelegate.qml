import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Dialogs 1.3
MenuDelegateForm {
    id: delegateForm
    itemImage.source: model.modelData.getImagePath(backend.getCurrentStallPath());
    property bool itemImageLoaded: false;
    property bool oosCheckboxLoaded: false;

    function check_data() {
        model.modelData.isValid = true;
        if (nameField.text == "") {
            nameField.placeholderText = "Name cannot be blank!";
            model.modelData.isValid = false;
        }
        console.log(index);
        for (var i = 0; i < menuViewModel.length; ++i) {
            // index is a delegate role, available automatically
            console.log(i);
            if(i !== index && menuViewModel[i].name === nameField.text) {
                nameField.text = "";
                nameField.placeholderText = "Another item with this name already exists!";
                model.modelData.isValid = false;
                break;
            }
        }
        if (descField.text == "") {
            descField.placeholderText = "Description cannot be blank!";
            model.modelData.isValid = false;
        }
        var priceFieldNum = parseFloat(priceField.text);
        if (isNaN(priceFieldNum) || priceFieldNum < 1) {
            priceField.text = "";
            priceField.placeholderText = "Must be >= 1!"
            model.modelData.isValid = false;
        }
        var estTimeFieldNum = parseFloat(estTimeField.text);
        if (isNaN(estTimeFieldNum) || estTimeFieldNum < 1) {
            estTimeField.text = "";
            estTimeField.placeholderText = "Must be >= 1!"
            model.modelData.isValid = false;
        }
        enable_buttons();
        return model.modelData.isValid;
    }

    nameField.onEditingFinished: {
        model.modelData.name = nameField.text;
        check_data();
    }

    descField.onEditingFinished: {
        model.modelData.description = descField.text;
        check_data();
    }

    priceField.onEditingFinished: {
        model.modelData.price = parseFloat(priceField.text);
        check_data();

    }
    estTimeField.onEditingFinished: {
        model.modelData.estimatedTime = parseFloat(estTimeField.text);
        check_data();
    }
    oosCheckbox.onCheckedChanged: { // this version waits for confirmation
        model.modelData.isOOS = oosCheckbox.checked;
        check_data();
    }
    categoryBox.onActivated: {
        model.modelData.type = categoryBox.currentText;
        check_data();

    }
    removeButton.onActivated: {
        enable_buttons();
        backend.proposeRemoveFood(index);
    }
    FileDialog {
        id: imageBrowser
        title: "Please choose an image for " + model.modelData.name
        folder: shortcuts.home
        nameFilters: [ "Image files (*.jpg *.png)", "All files (*)" ]
        selectExisting: true
        selectFolder: false
        selectMultiple: false
        onAccepted: {
            console.log("You chose: " + imageBrowser.fileUrl)
            itemImage.source = imageBrowser.fileUrl;
            model.modelData.setImagePath(backend.getCurrentStallName(),imageBrowser.fileUrl);
            enable_buttons();
            close()
        }
        onRejected: {
            console.log("Canceled")
            close()
        }
    }
    changeImageButton.onClicked: imageBrowser.open();
}
