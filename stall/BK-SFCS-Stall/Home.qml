import QtQuick 2.0
import QtQuick.Dialogs 1.3

HomeForm {
    Connections {
        target: sales
        function onTimeRangeChanged() {
            dataRangeStart.text = sales.getRangeLeftStr()
            dataRangeEnd.text = sales.getRangeRightStr()
        }
    }

    FileDialog {
        id: saveDialog
        title: "Please select a location to save the exported data"
        folder: shortcuts.home
        nameFilters: [ "Comma-separated values (*.csv)", "All files (*)" ]
        selectExisting: false
        selectFolder: false
        selectMultiple: false
        onAccepted: {
            console.log("Saving CSV to " + saveDialog)
            sales.advancedExport(respBox.checked, procBox.checked, qtyBox.checked, rejectBox.checked, saveDialog.fileUrl)
            close()
        }
        onRejected: {
            console.log("Canceled")
            close()
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

    dataRangeSlider.first.onMoved: sales.setStartRange(dataRangeSlider.first.position);
    dataRangeSlider.second.onMoved: sales.setEndRange(dataRangeSlider.second.position);
    advancedExportButton.onClicked: {
        saveDialog.open();
    }
}
