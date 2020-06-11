import QtQuick 2.0
import "../delegates"
WaitlistForm {
    refreshButton.onClicked: {
        backend.loadOrder();
    }

}
