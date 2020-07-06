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

void Sales::drawQuantityBarGraph(QAbstractSeries *series) {
    QAbstractBarSeries *barSeries = static_cast<QAbstractBarSeries *>(series);

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
        barSeries->append(set);
    }
}

void Sales::drawTimeLineGraph(QAbstractSeries *response, QAbstractSeries *processing) {
    QXYSeries *responseXYSeries = static_cast<QXYSeries *>(response);
    QXYSeries *processingXYSeries = static_cast<QXYSeries *>(processing);

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

        responseXYSeries->append(start.toMSecsSinceEpoch(), avg_response);
        processingXYSeries->append(start.toMSecsSinceEpoch(), avg_processing);

        start = start.addDays(1);
        end = end.addDays(1);
    }
}

void Sales::drawRejectedBarGraph(QAbstractSeries *series) {
    QAbstractBarSeries *barSeries = static_cast<QAbstractBarSeries *>(series);
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

    barSeries->append(set);
}

void Sales::advancedExport() {

}
