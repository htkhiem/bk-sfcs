import QtQuick 2.4
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.11

Page {
    id: page
    width: 1280
    height: 720
    property alias addButton: addButton

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
            model: stallViewModel
            delegate: StallDelegate {
                width: listView.width
                nameText.text: stallName
            }
        }
    }

    RoundButton {
        id: addButton
        enabled: true
        width: 40
        height: width
        background: Rectangle {
            width: parent.width
            height: parent.height
            radius: width / 2
            color: "#0033cc"
            opacity: enabled ? 1 : 0.2
        }
        contentItem: Text {
            text: parent.text
            font: parent.font
            opacity: enabled ? 1.0 : 0.2
            color: "#ffffff"
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            elide: Text.ElideRight
        }

        text: "+"
        highlighted: false
        flat: false
        anchors.bottom: scrollView.bottom
        anchors.bottomMargin: 10
        anchors.right: parent.right
        anchors.rightMargin: 10
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.25}
}
##^##*/

