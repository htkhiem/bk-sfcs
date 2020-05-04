import QtQuick 2.4

CategoryDelegateForm {
    property bool selected: true
    mouseArea.onClicked: {
        selected = !selected;
        if (selected == true) color = "8a8a8a"
        else color = "404040"
        console.log(selected)
    }
}
