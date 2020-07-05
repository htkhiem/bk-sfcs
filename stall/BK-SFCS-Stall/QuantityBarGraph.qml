import QtQuick 2.0
import QtCharts 2.3

ChartView {
    title: "Quantity of food items"
    legend.alignment: Qt.AlignBottom
    antialiasing: true

    BarSeries {
        id: quantityBarGraph
        axisX: BarCategoryAxis {
            categories: ["Item 1", "Item 2", "Item 3"]
        }
        BarSet: {
            label: "Number of orders";
            values: [2, 3, 4]
        }
    }
}
