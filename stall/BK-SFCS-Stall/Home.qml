import QtQuick 2.0

HomeForm {
    Connections {
        target: sales
        function onTimeRangeChanged() {
            dataRangeStart.text = sales.getRangeLeftStr()
            dataRangeEnd.text = sales.getRangeRightStr()
        }
    }

    Component.onCompleted: {
        dataRangeStart.text = sales.getRangeLeftStr()
        dataRangeEnd.text = sales.getRangeRightStr()
        for (var childIdx in gridView.contentItem.children) {
            gridView.contentItem.children[childIdx].loader.item.refresh();
        }
    }

    reloadGraphsButton.onClicked: {
        for (var childIdx in gridView.contentItem.children) {
            gridView.contentItem.children[childIdx].loader.item.refresh();
        }
    }
}
