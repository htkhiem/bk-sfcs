import QtQuick 2.0
import QtCharts 2.3

ChartView {
    id: chartView
    title: "Rejected orders"
    legend.alignment: Qt.AlignBottom
    antialiasing: true

//    property bool openGL: true
//    property bool openGLSupported: true
//    onOpenGLChanged: {
//        if (openGLSupported) {
//            series("signal 1").useOpenGL = openGL;
//            series("signal 2").useOpenGL = openGL;
//        }
//    }
//    Component.onCompleted: {
//        if (!series("signal 1").useOpenGL) {
//            openGLSupported = false
//            openGL = false
//        }
//    }



    BarSeries {
        id: rejectedBarGraph
    }

    function refresh() {
        sales.drawRejectedBarGraph(chartView.series(0))
    }
}
