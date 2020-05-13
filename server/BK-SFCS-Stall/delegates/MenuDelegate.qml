import QtQuick 2.0
import backend.qfood 1.0
MenuDelegateForm {
    id: delegateForm
    property bool dataValid: true;
    property bool itemImageLoaded: false;
    property bool oosCheckboxLoaded: false;
    function package_qfood() {
        var thisFood = thisFoodComponent.createObject(delegateForm);
        thisFood.name = nameField.text;
        thisFood.type = categoryBox.currentText;
        thisFood.description = descField.text;
        thisFood.isOOS = oosCheckbox.checked;
        thisFood.price = parseFloat(priceField.text);
        thisFood.estimatedTime = parseFloat(estTimeField.text);
        return thisFood;
    }
    function check_data() {
        dataValid = true;
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
        return dataValid;
    }

    Component {
        id: thisFoodComponent
        QFood {}
    }

    itemImage.onSourceChanged: {
        if (itemImageLoaded) {
            if (check_data())
                enable_buttons();
            backend.proposeEditFood(package_qfood(), index);
        }
        else itemImageLoaded = true;
    }
    nameField.onEditingFinished: {
        if (check_data()) {
            enable_buttons();
            backend.proposeEditFood(package_qfood(), index);
        }
    }

    descField.onEditingFinished: {
        if (check_data()) {
            enable_buttons();
            backend.proposeEditFood(package_qfood(), index)
        }
    }

    priceField.onEditingFinished: {
        if (check_data()) {
            enable_buttons();
            backend.proposeEditFood(package_qfood(), index);
        }
    }
    estTimeField.onEditingFinished: {
        if (check_data()) {
            enable_buttons();
            backend.proposeEditFood(package_qfood(), index);
        }
    }
    oosCheckbox.onCheckedChanged: { // this version waits for confirmation
        if (oosCheckboxLoaded) {
            if (check_data()) {
                enable_buttons();
                backend.proposeEditFood(package_qfood(), index);
            }
        }
        else oosCheckboxLoaded = true;
    }
    categoryBox.onActivated: {
        if (check_data()) {
            enable_buttons();
            backend.proposeEditFood(package_qfood(), delegateForm.index);
        }

    }
    removeButton.onActivated: {
        backend.proposeRemoveFood(index);
        enable_buttons();
    }
}
