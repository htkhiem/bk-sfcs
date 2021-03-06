import QtQuick 2.0
import QtCharts 2.3

ChartView {
    id: chartView
    title: "Quantity of food items"
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
        id: yAxis
        min: 0
        max: 20
    }

    BarSeries {
        id: quantityBarGraph
        axisX: BarCategoryAxis {
            categories: ["(incl. rejected orders)"]
        }
        axisY: yAxis
    }

    function refresh() {
        yAxis.max = sales.drawQuantityBarGraph(chartView.series(0))
    }
}
