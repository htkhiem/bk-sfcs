import QtQuick 2.4

SimpleMenuDelegateForm {
    itemImage.source: model.modelData.getImagePath(backend.getCurrentStallPath());
    oosCheckbox.onCheckedChanged: {
        model.modelData.isOOS = oosCheckbox.checked;
        backend.applyProposal(); // no need to update images
    }
}
