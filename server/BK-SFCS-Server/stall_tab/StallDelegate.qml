import QtQuick 2.4

StallDelegateForm {
    property int clientIdx: -1 // -1 means not connected
    Component.onCompleted: {
        image.source = server.getStallImagePath(index);
        clientIdx = server.getStallClientIdx(index);
        if (clientIdx != -1) {
            onlineStatus.visible = true;
            disconnectButton.enabled = true;
            removeButton.enabled = false;
        }
        else {
            onlineStatus.visible = false;
            disconnectButton.enabled = false;
            removeButton.enabled = true;
        }
    }
    disconnectButton.onClicked: {
        if (clientIdx != -1) server.disconnect(clientIdx);
    }
    removeButton.onClicked: {
        if (clientIdx == -1) server.removeStall(index);
    }
}
