import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.11

ApplicationWindow {
    id: window
    visible: true
    width: 1280
    height: 720
    title: qsTr("Smart Food Court System")

    header: ToolBar {
        contentHeight: backButton.implicitHeight
        RowLayout {
            anchors.fill: parent
            ToolButton {
                id: backButton
                text: "‹ Back"  // icon
                visible: stackView.depth > 1 ? true : false
                font.pixelSize: Qt.application.font.pixelSize * 1.6
                onClicked: {
                    stackView.pop()
                }
            }

            Label {
                text: stackView.currentItem.title
                anchors.centerIn: parent
                Layout.fillWidth: true
                elide: Label.ElideRight
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
            }

            ToolButton {
                id: searchButton
                text: "Search 🔎"
                visible: stackView.depth > 1 ? true : false
                onClicked: {
                    searchPopup.open()
                }
            }
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
    SearchPopup {
        id: searchPopup
    }

    function openMenu(stallName) {
        stallMenuForm.title = stallName;
        stackView.push(stallMenuForm)
    }
}
