import QtQuick 2.0
import QtCharts 2.3

ChartView {
    id: chartView
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
    ValueAxis {
        id: xAxis
        min: 0
        max: 4
    }

    ValueAxis {
        id: yAxis
        min: 0
        max: 100
    }

    LineSeries {
        name: "Response time"
        axisX: xAxis
        axisY: yAxis
    }

    LineSeries {
        name: "Processing time"
        axisX: xAxis
        axisY: yAxis
    }

    function refresh() {
        yAxis.max = sales.drawTimeLineGraph(chartView.series(0), chartView.series(1))
        xAxis.max = sales.getRangeLength();
    }
}
