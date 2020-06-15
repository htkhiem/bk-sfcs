#include "sales.h"

sales::sales(QObject *parent) : QObject(parent) {

}

double sales::getRevenue(QDateTime date) {
    for (int i = 0; i < salesData.size(); i++) {

    }
}

void sales::updateOldestDate(QDateTime date) {
    if (date.daysTo(latestDate) <= 30)
        oldestDate = date;
}

void sales::updateLatestDate(QDateTime date) {
    if (oldestDate.daysTo(date) <= 30)
        latestDate = date;
}

QBarSeries sales::drawRevenueBarGraph() {
    QBarSeries *revenue = new QBarSeries();

}

QBarSeries sales::drawQuantityBarGraph() {
    QBarSeries *quantity = new QBarSeries();

}

QLineSeries sales::drawTimeLineGraph() {
    QLineSeries *response = new QLineSeries();
    QLineSeries *processing = new QLineSeries();

    QDateTime start = oldestDate;
    start.setTime(QTime());
    QDateTime end = start.addSecs(86399);
    while (end <= latestDate) {
        int avg_response = 0, avg_processing = 0, n = 0;
        for (int i = 0; i < salesData.size(); i++) {
            if (start <= salesData[i].getFinished() && salesData[i].getFinished() <= end) {
                avg_response += salesData[i].getResponseTime();
                avg_processing += salesData[i].getProcessingTime();
                n++;
            }
        }
        avg_response /= n;
        avg_processing /= n;
        response->append(start.toMSecsSinceEpoch(), avg_response);
        processing->append(start.toMSecsSinceEpoch(), avg_processing);
        start = start.addDays(1);
        end = end.addDays(1);
    }

    QChart *chart = new QChart();
    chart->addSeries(response);
    chart->addSeries(processing);
    chart->legend()->hide();
    chart->setTitle("Response and Processing Time");

    QDateTimeAxis *axisX = new QDateTimeAxis;
    axisX->setTickCount(10);
    axisX->setFormat("dd:mm:yyyy");
    axisX->setTitleText("Date");
    chart->addAxis(axisX, Qt::AlignBottom);
    response->attachAxis(axisX);
    processing->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis;
    axisY->setLabelFormat("%i");
    axisY->setTitleText("Seconds");
    chart->addAxis(axisY, Qt::AlignLeft);
    response->attachAxis(axisY);
    processing->attachAxis(axisY);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QMainWindow window;
    window.setCentralWidget(chartView);
    window.resize(820, 600);
    window.show();
}

QBarSeries sales::drawRejectedBarGraph() {
    QBarSeries *rejected = new QBarSeries();

}

void sales::advancedExport() {

}
