import QtQuick 2.0
import QtCharts 2.3

ChartView {
    title: "Quantity of food items"
    legend.alignment: Qt.AlignBottom
    antialiasing: true

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


    BarSeries {
        id: quantityBarGraph
        axisX: BarCategoryAxis {
            categories: ["Item 1", "Item 2", "Item 3"]
        }
        BarSet {
            label: "Number of orders";
            values: [2, 3, 4]
        }
    }
}
