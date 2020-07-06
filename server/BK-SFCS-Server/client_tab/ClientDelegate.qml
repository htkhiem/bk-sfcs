import QtQuick 2.4

ClientDelegateForm {
    disconnectButton.onClicked: server.disconnect(index);
}
