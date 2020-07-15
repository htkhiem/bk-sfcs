import QtQuick 2.4

UnsavedChangesPopupForm {
    property string nextPath: ""
    yesButton.onClicked: {
        load(nextPath);
        deactivateConfirmExit()
        close();
    }
    noButton.onClicked: {
        deactivateConfirmExit()
        close();
    }
}
