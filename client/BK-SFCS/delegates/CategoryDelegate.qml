import QtQuick 2.4

CategoryDelegateForm {
    property color enabledGradStart: gradStart.color
    property color enabledGradEnd: gradEnd.color
    property color disabledGradStart: Qt.lighter(gradStart.color)
    property color disabledGradEnd: Qt.lighter(gradEnd.color)
    onClicked: {
        if (checked) {
            gradStart.color = enabledGradStart;
            gradEnd.color = enabledGradEnd;
        }
        else {
            gradStart.color = disabledGradStart;
            gradEnd.color = disabledGradEnd;
        }
    }
}
