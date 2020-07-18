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
        rejectGraph.refresh();
        qtyGraph.refresh();
        timeGraph.refresh();
    }

    reloadGraphsButton.onClicked: {
        rejectGraph.refresh();
        qtyGraph.refresh();
        timeGraph.refresh();
    }

    advancedExportButton.onClicked: {

    }
}
