import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.11
import QtGraphicalEffects 1.14

ApplicationWindow {
    id: window
    visible: true
    width: 1280
    height: 720
    title: qsTr("Smart Food Court System")

    header: ToolBar {
        background: Rectangle {
            id: toolBarBg
            implicitHeight: 65
            color: "#ff5555"
            DropShadow {
                anchors.fill: parent
                horizontalOffset: 0
                verticalOffset: 3
                radius: 8.0
                samples: 12
                cached: true
                color: "#80000000"
                source: parent
            }
        }

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
                color: "#ffffff"
                font.pointSize: 18
                font.bold: true
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
    StallMenu {
        id: stallMenu
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
    FastBlur {
        id: bgBlur
        anchors.fill: parent
        source: parent
        radius: 32
        visible: false
        cached: true // higher perf
    }

    function openMenu(stallIdx) {
        backend.setCurrentStall(stallIdx);
        backend.populateMenuViewModel();
        stallMenu.title = stallViewModel[stallIdx].stallName;
        stackView.push(stallMenu)
    }

    function blurUnfocused() {
        bgBlur.visible = true;
    }
    function refocus() {
        bgBlur.visible = false;
    }
}
