import QtQuick 2.0
MenuDelegateForm {
    property int itemImageChangeTimes: 0;
    property int oosCheckboxChangeTimes: 0;
    itemImage.onSourceChanged: {
        itemImageChangeTimes++;
        if (itemImageChangeTimes > 1)
            enable_buttons()
    }
    nameField.onEditingFinished: {
        enable_buttons()
    }

    descField.onEditingFinished: {
        enable_buttons()
    }

    priceField.onEditingFinished: {
        enable_buttons()
    }

    oosCheckbox.onCheckedChanged: {
        oosCheckboxChangeTimes++;
        if(oosCheckboxChangeTimes > 1)
            enable_buttons()
    }
}
