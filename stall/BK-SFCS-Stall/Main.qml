import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import "./popups"

MainForm {
    DisconnectPopup {
        id: disconnectPopup
        x: Math.round((parent.width - width) / 2)
        y: Math.round((parent.height - height) / 2)
    }
    Connections {
        target: backend
        function onConnectionLost() {
            disconnectPopup.open(); // No way to turn off except restart
        }
    }
}
