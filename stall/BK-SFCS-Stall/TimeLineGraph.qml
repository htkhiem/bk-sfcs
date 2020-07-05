import QtQuick 2.0
import QtCharts 2.3

ChartView {
    title: "Response and processing time"
    legend.alignment: Qt.AlignBottom
    antialiasing: true

    LineSeries {
        name: "Response time"
        XYPoint { x: 0; y: 0 }
        XYPoint { x: 1.1; y: 2.1 }
        XYPoint { x: 1.9; y: 3.3 }
    }

    LineSeries {
        name: "Processing time"
        XYPoint { x: 2.1; y: 2.1 }
        XYPoint { x: 2.9; y: 4.9 }
        XYPoint { x: 3.4; y: 3.0 }
    }
}
