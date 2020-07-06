import QtQuick 2.0
import QtCharts 2.3

ChartView {
    title: "Response and processing time"
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

    LineSeries {
        name: "Response time"
        //XYPoint { x: 0; y: 0 }
        //XYPoint { x: 1.1; y: 2.1 }
        //XYPoint { x: 1.9; y: 3.3 }
    }

    LineSeries {
        name: "Processing time"
        //XYPoint { x: 2.1; y: 2.1 }
        //XYPoint { x: 2.9; y: 4.9 }
        //XYPoint { x: 3.4; y: 3.0 }
    }

    function refresh() {
        sales.drawRejectedBarGraph(chartView.series(0))
    }
}
