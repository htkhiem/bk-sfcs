import QtQuick 2.4

CategoryDelegateForm {
    property color enabledGradStart: gradStart.color
    property color enabledGradEnd: gradEnd.color
    onClicked: {
        if (checked) {
            opacity = 1;
            model.modelData.toggleVisibility(true);
            searchMenu()
        }
        else {
            opacity = 0.3;
            model.modelData.toggleVisibility(false);
            searchMenu()
        }
    }
}
