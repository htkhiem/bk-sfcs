#include "sales.h"

Sales::Sales(QObject *parent) : QObject(parent) {

}

void Sales::updateOldestDate(QDateTime date) {
    if (date.daysTo(latestDate) <= 30)
        oldestDate = date;
}

void Sales::updateLatestDate(QDateTime date) {
    if (oldestDate.daysTo(date) <= 30)
        latestDate = date;
}

QBarSeries Sales::drawQuantityBarGraph() {
    QBarSeries *quantity = new QBarSeries();

    QDateTime start = oldestDate;
    start.setTime(QTime());
    QDateTime end = start.addSecs(86399);
    QVector<QPair<QString, int>> foodList;
    while (end <= latestDate) {
        for (int i = 0; i < salesData.size(); i++) {
            OrderInfo& od = *(OrderInfo *) salesData[i];
            if (start <= od.getFinished() && od.getFinished() <= end) {
                for (int j = 0; j < foodList.size(); j++) {
                    if (foodList[i].first == od.getItemName())
                        foodList[i].second += od.getQuantity();
                    else
                        foodList.push_back(qMakePair(od.getItemName(), od.getQuantity()));
                }
            }
        }
        start = start.addDays(1);
        end = end.addDays(1);
    }

    for (int i = 0; i < foodList.size(); i++) {
        QBarSet *set = new QBarSet(foodList[i].first);
        *set << foodList[i].second;
        quantity->append(set);
    }

    QChart *chart = new QChart();
    chart->addSeries(quantity);
    chart->legend()->hide();
    chart->setTitle("Quantity Chart");

    QDateTimeAxis *axisX = new QDateTimeAxis;
    axisX->setTickCount(10);
    axisX->setFormat("dd:mm:yyyy");
    axisX->setTitleText("Date");
    chart->addAxis(axisX, Qt::AlignBottom);
    quantity->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis;
    axisY->setLabelFormat("%i");
    axisY->setTitleText("Orders");
    chart->addAxis(axisY, Qt::AlignLeft);
    quantity->attachAxis(axisY);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QMainWindow window;
    window.setCentralWidget(chartView);
    window.resize(820, 600);
    window.show();
}

QLineSeries Sales::drawTimeLineGraph() {
    QLineSeries *response = new QLineSeries();
    QLineSeries *processing = new QLineSeries();

    QDateTime start = oldestDate;
    start.setTime(QTime());
    QDateTime end = start.addSecs(86399);
    while (end <= latestDate) {
        int avg_response = 0, avg_processing = 0, n = 0;
        for (int i = 0; i < salesData.size(); i++) {
            OrderInfo& od = *(OrderInfo *) salesData[i];
            if (start <= od.getFinished() && od.getFinished() <= end) {
                avg_response += od.getResponseTime();
                avg_processing += od.getProcessingTime();
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
    chart->setTitle("Response and Processing Time Per Day");

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

QBarSeries Sales::drawRejectedBarGraph() {
    QBarSeries *rejected = new QBarSeries();
    QBarSet *set = new QBarSet("Rejected Order");

    QDateTime start = oldestDate;
    start.setTime(QTime());
    QDateTime end = start.addSecs(86399);
    while (end <= latestDate) {
        int reject = 0;
        for (int i = 0; i < salesData.size(); i++) {
            OrderInfo& od = *(OrderInfo *) salesData[i];
            if (start <= od.getFinished() && od.getFinished() <= end) {
                if (od.getStatus() == OrderStatus::rejected) reject++;
            }
        }
        *set << reject;
        start = start.addDays(1);
        end = end.addDays(1);
    }
    rejected->append(set);

    QChart *chart = new QChart();
    chart->addSeries(rejected);
    chart->legend()->hide();
    chart->setTitle("Rejected Order Per Day");

    QDateTimeAxis *axisX = new QDateTimeAxis;
    axisX->setTickCount(10);
    axisX->setFormat("dd:mm:yyyy");
    axisX->setTitleText("Date");
    chart->addAxis(axisX, Qt::AlignBottom);
    rejected->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis;
    axisY->setLabelFormat("%i");
    axisY->setTitleText("Orders");
    chart->addAxis(axisY, Qt::AlignLeft);
    rejected->attachAxis(axisY);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QMainWindow window;
    window.setCentralWidget(chartView);
    window.resize(820, 600);
    window.show();
}

void Sales::advancedExport() {

}
