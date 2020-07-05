import QtQuick 2.0

HomeForm {
    id: homeForm
    property bool openGL: true
    property bool openGLSupported: true
    onOpenGLChanged: {
        if (openGLSupported) {
            series("signal 1").useOpenGL = openGL;
            series("signal 2").useOpenGL = openGL;
        }
    }
    Component.onCompleted: {
        if (!series("signal 1").useOpenGL) {
            openGLSupported = false
            openGL = false
        }
    }

    GridView {
        id: gridView
        x: 10
        y: 182
        width: 140
        height: 140
        cellWidth: width/2
        cellHeight: height/2
        model: ListModel {
            ListElement {
                component: "QuantityBarGraph.qml"
            }
            ListElement {
                component: "TimeLineGraph"
            }
            ListElement {
                component: "RejectedBarGraph.qml"
            }
        }
    }
}
