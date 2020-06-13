import QtQuick 2.4

SimpleMenuDelegateForm {
    Connections {
        target: backend
        function onItemImageChanged(sidx, midx) {
            if (sidx === backend.getCurrentStallIdx() && midx === index) {
                backend.getItemImagePath(midx);
            }
        }
    }

    itemImage.source: backend.getItemImagePath(index)
    oosCheckbox.onCheckedChanged: {
        model.modelData.isOOS = oosCheckbox.checked;
        backend.applyProposal(); // no need to update images
    }
}
