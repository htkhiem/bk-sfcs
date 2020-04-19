import QtQuick 2.12
import QtQuick.Controls 2.5

ApplicationWindow {
    id: window
    visible: true
    width: 1280
    height: 720
    title: qsTr("Smart Food Court System")

    header: ToolBar {
        contentHeight: backButton.implicitHeight

        ToolButton {
            id: backButton
            text: "\u25c0"  // icon
            visible: stackView.depth > 1 ? true : false
            font.pixelSize: Qt.application.font.pixelSize * 1.6
            onClicked: {
                if (stackView.depth > 1) {
                    stackView.pop()
                } else {
                    drawer.open()
                }
            }
        }

        Label {
            text: stackView.currentItem.title
            anchors.centerIn: parent
        }
    }
    HomeForm {
        id: homeForm
        anchors.fill: parent
    }
    StallMenuForm {
        id: stallMenuForm
        anchors.fill: parent
    }
    StackView {
        id: stackView
        initialItem: homeForm
        anchors.fill: parent
    }
    function openMenu(stallName) {
        stallMenuForm.title = stallName;
        stackView.push(stallMenuForm)
    }
}
