import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Dialogs 1.3
MenuDelegateForm {
    id: delegateForm
    Connections {
        target: backend
        function onItemImageChanged(sidx, midx) {
            if (sidx === backend.getCurrentStallIdx() && midx === index) {
                backend.getItemImagePath(midx);
            }
        }
    }
    itemImage.source: backend.getItemImagePath(index)
    property bool itemImageLoaded: false;
    property bool oosCheckboxLoaded: false;

    function check_data() {
        model.modelData.isValid = true;
        if (nameField.text === "") {
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
        if (descField.text === "") {
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
        return model.modelData.isValid;
    }

    nameField.onEditingFinished: {
        model.modelData.name = nameField.text;
        if (check_data) {
            enable_buttons();
        }
    }

    descField.onEditingFinished: {
        model.modelData.description = descField.text;
        if (check_data()) {
            enable_buttons();
        }
    }

    priceField.onEditingFinished: {
        model.modelData.price = parseFloat(priceField.text);
        if (check_data()) {
            enable_buttons();
        }

    }
    estTimeField.onEditingFinished: {
        model.modelData.estimatedTime = parseFloat(estTimeField.text);
        if (check_data()) {
            enable_buttons();
        }
    }
    oosCheckbox.onCheckedChanged: { // this version waits for confirmation
        model.modelData.isOOS = oosCheckbox.checked;
        if (check_data()) {
            enable_buttons();
        }
    }
    categoryBox.onActivated: {
        model.modelData.type = categoryBox.currentText;
        if (check_data()) {
            enable_buttons();
        }

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
            console.log("You chose: " + imageBrowser.fileUrl);
            itemImage.source = imageBrowser.fileUrl;
            backend.setItemImage(imageBrowser.fileUrl, index);
            enable_buttons();
            markUpdateImages();
            close()
        }
        onRejected: {
            console.log("Canceled")
            close()
        }
    }
    changeImageButton.onClicked: imageBrowser.open();
}
