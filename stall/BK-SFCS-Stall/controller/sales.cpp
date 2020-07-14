#include "sales.h"

Sales::Sales(QObject *parent) : QObject(parent) {
    loadData();
    getOldestDate();
    getLatestDate();
}

void Sales::loadData() {
    QDir data_cursor = QDir::home();
    data_cursor.mkdir("BK-SFCS Stall Manager");
    data_cursor.cd("BK-SFCS Stall Manager");

    data_cursor.setFilter(QDir::Dirs | QDir::NoDotAndDotDot);
    QStringList stall_dirs = data_cursor.entryList();
    for (auto qstr : stall_dirs) {
        data_cursor.cd(qstr);
        if (data_cursor.cd("logs")) {
            QDir log_dir = data_cursor;
            log_dir.setFilter(QDir::Files | QDir::NoDotAndDotDot);
            QStringList log_list = log_dir.entryList();
            //read json files
            for (auto log : log_list) {
                QFile log_file(log_dir.filePath(log));
                if (!log_file.open(QIODevice::ReadOnly))
                    throw runtime_error("Cannot read data file: " + log.toStdString());

                QJsonDocument log_json_doc(QJsonDocument::fromJson(log_file.readAll()));
                OrderInfo* order_info = new OrderInfo();
                order_info->read(log_json_doc.object());
                salesData.append(order_info);
                log_file.close();
            }

            data_cursor.cdUp();
            data_cursor.cdUp();
        }
        else
            data_cursor.cdUp();
    }
}

void Sales::getOldestDate() {
    if (salesData.first()->getStatus() == OrderStatus::rejected)
        oldestDate = salesData.first()->getAnswered();
    else
        oldestDate = salesData.first()->getFinished();
}

void Sales::getLatestDate() {
    if (salesData.last()->getStatus() == OrderStatus::rejected)
        latestDate = salesData.last()->getAnswered();
    else
        latestDate = salesData.last()->getFinished();
}

void Sales::setStartRange(double pos) {
    rangeLeft = oldestDate.addMSecs((latestDate.toMSecsSinceEpoch() - oldestDate.toMSecsSinceEpoch()) * pos);
}

void Sales::setEndRange(double pos) {
    rangeRight = latestDate.addMSecs((latestDate.toMSecsSinceEpoch() - oldestDate.toMSecsSinceEpoch()) * pos);
}

void Sales::drawQuantityBarGraph(QAbstractSeries *series) {
    QAbstractBarSeries *barSeries = static_cast<QAbstractBarSeries *>(series);

    QDateTime start = rangeLeft;
    start.setTime(QTime());
    QDateTime end = start.addSecs(86399);
    QVector<QPair<QString, int>> foodList;

    while (end <= rangeRight) {
        for (int i = 0; i < salesData.size(); i++) {
            OrderInfo& od = *salesData[i];
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

    QDateTime start = rangeLeft;
    start.setTime(QTime());
    QDateTime end = start.addSecs(86399);

    while (end <= rangeRight) {
        int avg_response = 0, avg_processing = 0, n = 0;
        for (int i = 0; i < salesData.size(); i++) {
            OrderInfo& od = *salesData[i];
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

    QDateTime start = rangeLeft;
    start.setTime(QTime());
    QDateTime end = start.addSecs(86399);

    while (end <= rangeRight) {
        int reject = 0;
        for (int i = 0; i < salesData.size(); i++) {
            OrderInfo& od = *salesData[i];
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
