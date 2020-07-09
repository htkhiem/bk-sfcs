import QtQuick 2.4

StallListForm {
    StallCreationWizard {
        popup.x: Math.round((parent.width - width) / 2)
        popup.y: Math.round((parent.height - height) / 2)
        id: wizard
    }
    addButton.onClicked: wizard.popup.open()
}
