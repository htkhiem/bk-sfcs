import QtQuick 2.4

SimpleMenuDelegateForm {
    itemImage.source: model.modelData.getImagePath(backend.getCurrentStallName());
    oosCheckbox.onCheckedChanged: {
        model.modelData.isOOS = oosCheckbox.checked;
    }
}
