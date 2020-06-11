import QtQuick 2.0

WaitlistForm {
    refreshButton.onClicked: {
        backend.loadOrder();
    }
}
