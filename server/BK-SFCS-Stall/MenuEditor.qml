import QtQuick 2.0

MenuEditorForm {
    property bool needsConfirmation: false
    function require_confirmation() {
        needsConfirmation = true;
        enable_buttons();
    }
    function enable_buttons() {
        confirmButton.enabled = true;
        revertButton.enabled = true;
    }
}
