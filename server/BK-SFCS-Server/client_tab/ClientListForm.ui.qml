import QtQuick 2.4
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.11

Page {
    width: 1280
    height: 720

    ScrollView {
        id: scrollView
        spacing: 5
        anchors.fill: parent
        clip: true
        ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
        ScrollBar.vertical.policy: ScrollBar.AlwaysOn
        ListView {
            id: listView
            width: scrollView.width
            height: scrollView.height
            bottomMargin: 0
            model: clientViewModel
            delegate: ClientDelegate {
                width: listView.width
                clientTypeText.text: isStall ? qsTr("STALL") : qsTr("KIOSK")
                clientTypeText.color: isStall ? "green" : "black"
                clientIdText.text: id
            }
        }
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.25}
}
##^##*/
