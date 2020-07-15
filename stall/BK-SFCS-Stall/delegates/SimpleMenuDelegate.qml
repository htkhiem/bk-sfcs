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
    oosCheckbox.onToggled: { // toggled() is only triggered via user interaction, not initialisation
        model.modelData.isOOS = oosCheckbox.checked;
        backend.applyProposal(); // no need to update images
    }
}
