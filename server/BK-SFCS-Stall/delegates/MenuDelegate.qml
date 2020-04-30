import QtQuick 2.0
MenuDelegateForm {
    property int itemImageChangeTimes: 0;
    property int nameFieldChangeTimes: 0;
    property int descFieldChangeTimes: 0;
    property int priceFieldChangeTimes: 0;
    property int oosCheckboxChangeTimes: 0;
    itemImage.onSourceChanged: {
        itemImageChangeTimes++;
        if (itemImageChangeTimes > 1)
            require_confirmation()
    }
    nameField.onTextChanged: {
        nameFieldChangeTimes++;
        if (nameFieldChangeTimes > 1)
            require_confirmation()
    }

    descField.onTextChanged: {
        descFieldChangeTimes++;
        if (descFieldChangeTimes > 1)
            require_confirmation()
    }

    priceField.onTextChanged: {
        priceFieldChangeTimes++;
        if (priceFieldChangeTimes > 1)
            require_confirmation()
    }

    oosCheckbox.onCheckedChanged: {
        oosCheckboxChangeTimes++;
        if(oosCheckboxChangeTimes > 1)
            enable_buttons()
    }
}
