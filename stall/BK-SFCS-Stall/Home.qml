import QtQuick 2.0

HomeForm {
    reloadGraphsButton.onClicked: {
        for (var child in gridView.contentItem.children) {
            child.refresh();
        }
    }

}
