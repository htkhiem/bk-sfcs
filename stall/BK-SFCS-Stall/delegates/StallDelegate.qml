import QtQuick 2.4
import "../"
StallDelegateForm {
    Connections {
        target: backend
        function onStallImageChanged(idx) {
            if (index === idx) stallImage.source = backend.getStallImagePath(idx);
        }
    }
    stallImage.source: backend.getStallImagePath(index);

    stallMouseArea.onClicked: {
        console.log(stallName.text)
        setCurrentIdx(index)
    }
}
