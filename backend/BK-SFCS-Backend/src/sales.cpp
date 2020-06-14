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
    for (int i = 0; i < salesData.size(); i++) {
        if (salesData[i].getFinished().date() == QDateTime::currentDateTime().date()) {

        }
    }
}

QBarSeries sales::drawQuantityBarGraph() {
    QBarSeries *quantity = new QBarSeries();
    for (int i = 0; i < salesData.size(); i++) {
        if (salesData[i].getFinished().date() == QDateTime::currentDateTime().date()) {

        }
    }
}

QLineSeries sales::drawTimeLineGraph() {
    QLineSeries *response = new QLineSeries();
    QLineSeries *processing = new QLineSeries();
    for (int i = 0; i < salesData.size(); i++) {
        if (salesData[i].getFinished().date() == QDateTime::currentDateTime().date()) {
            response->append(salesData[i].getFinished().toMSecsSinceEpoch(), salesData[i].getResponseTime());
            processing->append(salesData[i].getFinished().toMSecsSinceEpoch(), salesData[i].getProcessingTime());
        }
    }

    QChart *chart = new QChart();
    chart->addSeries(response);
    chart->addSeries(processing);
    chart->legend()->hide();
    chart->setTitle("Response and Processing Time");

    QDateTimeAxis *axisX = new QDateTimeAxis;
    axisX->setTickCount(10);
    axisX->setFormat("hh:mm:ss");
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
    for (int i = 0; i < salesData.size(); i++) {
        if (salesData[i].getFinished().date() == QDateTime::currentDateTime().date()) {

        }
    }
}

void sales::advancedExport() {

}
