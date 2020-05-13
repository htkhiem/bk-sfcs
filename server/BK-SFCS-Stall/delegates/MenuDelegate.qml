import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Dialogs 1.3
MenuDelegateForm {
    id: delegateForm
    itemImage.source: model.modelData.getImagePath(backend.getCurrentStallName());
    property bool itemImageLoaded: false;
    property bool oosCheckboxLoaded: false;

    function check_data() {
        var dataValid = true;
        if (nameField.text == "") {
            nameField.placeholderText = "Name cannot be blank!";
            dataValid = false;
        }
        console.log(index);
        for (var i = 0; i < menuViewModel.length; ++i) {
            // index is a delegate role, available automatically
            console.log(i);
            if(i !== index && menuViewModel[i].name === nameField.text) {
                nameField.text = "";
                nameField.placeholderText = "Another item with this name already exists!";
                dataValid = false;
                break;
            }
        }
        if (descField.text == "") {
            descField.placeholderText = "Description cannot be blank!";
            dataValid = false;
        }
        var priceFieldNum = parseFloat(priceField.text);
        if (isNaN(priceFieldNum) || priceFieldNum < 1) {
            priceField.text = "";
            priceField.placeholderText = "Must be >= 1!"
            dataValid = false;
        }
        var estTimeFieldNum = parseFloat(estTimeField.text);
        if (isNaN(estTimeFieldNum) || estTimeFieldNum < 1) {
            estTimeField.text = "";
            estTimeField.placeholderText = "Must be >= 1!"
            dataValid = false;
        }
        model.modelData.isValid = dataValid;
        enable_buttons();
        return dataValid;
    }


    itemImage.onSourceChanged: {
        if (itemImageLoaded) {
            if (check_data())
            model.modelData.setImagePath(backend.getCurrentStallName(), imageBrowser.fileUrl);
        }
        else itemImageLoaded = true;
    }
    nameField.onEditingFinished: {
        if (check_data()) {
            model.modelData.name = nameField.text;
        }
    }

    descField.onEditingFinished: {
        if (check_data()) {
            model.modelData.name.description = descField.text;
        }
    }

    priceField.onEditingFinished: {
        if (check_data()) {
            model.modelData.name.price = parseFloat(priceField.text);
        }
    }
    estTimeField.onEditingFinished: {
        if (check_data()) {
            model.modelData.name.estimatedTime = parseFloat(estTimeField.text);
        }
    }
    oosCheckbox.onCheckedChanged: { // this version waits for confirmation
        if (oosCheckboxLoaded) {
            if (check_data()) {
                model.modelData.name.isOOS = oosCheckbox.checked;
            }
        }
        else oosCheckboxLoaded = true;
    }
    categoryBox.onActivated: {
        if (check_data()) {
            model.modelData.name.type = categoryBox.currentText;
        }

    }
    removeButton.onActivated: {
        backend.proposeRemoveFood(index);
        enable_buttons();
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
            close()
        }
        onRejected: {
            console.log("Canceled")
            close()
        }
    }
    changeImageButton.onClicked: {
        imageBrowser.open();
        if (check_data()) {
        model.modelData.setImagePath(backend.getCurrentStallName(),imageBrowser.fileUrl);
        }
    }
}
