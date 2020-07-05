import QtQuick 2.0
import QtCharts 2.3

ChartView {
    title: "Rejected orders"
    legend.alignment: Qt.AlignBottom
    antialiasing: true

    BarSeries {
        id: rejectedBarGraph
        axisX: BarCategoryAxis {
            categories: ["11/11/1111", "22/22/2222", "33/33/3333"]
        }
        BarSet: {
            label: "Number of orders";
            values: [2, 3, 4]
        }
    }
}
