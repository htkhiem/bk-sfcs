import QtQuick 2.4

StallDelegateForm {
    Connections {
        target: backend
        function onStallImageChanged(idx) {
            if (idx === index)
                stallImage.source = backend.getStallImagePath(idx);
        }
    }
    stallImage.source: backend.getStallImagePath(index)
    stallMouseArea.onClicked: {
        console.log(index)
        openMenu(index)
    }
}
