import QtQuick 2.12
import QtQuick.Controls 2.5
import "../delegates"

Page {
    property alias waitlistLoader: waitlistLoader
    id: page
    width: 1280
    height: 720
    anchors.fill: parent
    title: qsTr("Waitlist")
    ScrollView {
        id: scrollView
        anchors.fill: parent
        clip: true
        ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
        ScrollBar.vertical.policy: ScrollBar.AlwaysOn
        Loader {
            id: waitlistLoader
            anchors.fill: parent
            sourceComponent: waitlistview
        }
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.75}
}
##^##*/

