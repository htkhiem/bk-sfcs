import QtQuick 2.4
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.11
import QtGraphicalEffects 1.14

Page {
    width: 1280
    height: 720
    property alias stackView: stackView
    property alias backButton: backButton
    property alias searchButton: searchButton
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
                text: (isSearching) ? "‹ End searching" : "‹ Back"
                contentItem: Text {
                    text: parent.text
                    color: "#ffffff"
                    font.pointSize: 16
                    verticalAlignment: Qt.AlignVCenter
                }
                visible: stackView.depth > 1 ? true : false
                font.pixelSize: Qt.application.font.pixelSize * 1.6
            }

            Label {
                text: stackView.currentItem.item.title
                Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter
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
                contentItem: Text {
                    text: "Search 🔎"
                    color: "#ffffff"
                    font.pointSize: 16
                    verticalAlignment: Qt.AlignVCenter
                }

            }
        }
    }
    StackView {
        id: stackView
        initialItem: homeFormLoader
        anchors.fill: parent
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.75}
}
##^##*/

