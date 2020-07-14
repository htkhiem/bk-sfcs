#include <QHash>
#include "sales.h"

QString Sales::getRangeLeftStr() const
{
  return rangeLeft.toString("dd.MM.yyyy");
}

QString Sales::getRangeRightStr() const
{
  return rangeRight.toString("dd.MM.yyyy");
}

Sales::Sales(QObject *parent) : QObject(parent) {
}

void Sales::loadData(const QString& stall_name) {
    QDir data_cursor = QDir::home();
    data_cursor.mkdir("BK-SFCS Stall Manager");
    data_cursor.cd("BK-SFCS Stall Manager");
    data_cursor.cd(stall_name);
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
    }
    getOldestDate();
    getLatestDate();
}

void Sales::getOldestDate() {
  if (salesData.first()->getStatus() == OrderStatus::rejected)
      oldestDate = salesData.first()->getAnswered();
  else
      oldestDate = salesData.first()->getFinished();
  oldestDate.fromSecsSinceEpoch(oldestDate.toSecsSinceEpoch() % 86400);
  emit timeRangeChanged();
}

void Sales::getLatestDate() {
    if (salesData.last()->getStatus() == OrderStatus::rejected)
        latestDate = salesData.last()->getAnswered();
    else
        latestDate = salesData.last()->getFinished();
    latestDate.fromSecsSinceEpoch(latestDate.toSecsSinceEpoch() % 86400 + 86400);
    emit timeRangeChanged();
}

void Sales::setStartRange(double pos) {
    rangeLeft = oldestDate.addMSecs((latestDate.toMSecsSinceEpoch() - oldestDate.toMSecsSinceEpoch()) * pos);
    rangeLeft.fromSecsSinceEpoch(rangeLeft.toSecsSinceEpoch() % 86400);
}

void Sales::setEndRange(double pos) {
    rangeRight = latestDate.addMSecs((latestDate.toMSecsSinceEpoch() - oldestDate.toMSecsSinceEpoch()) * pos);
    rangeRight.fromSecsSinceEpoch(rangeRight.toSecsSinceEpoch() % 86400 + 86400);
}

unsigned Sales::drawQuantityBarGraph(QAbstractSeries *series) {
    QAbstractBarSeries *barSeries = static_cast<QAbstractBarSeries *>(series);
    barSeries->clear();
    QDateTime start = rangeLeft;
    start.setTime(QTime());
    QDateTime end = start.addSecs(86399);
    QHash<QString, unsigned> food_counts;

    unsigned max_quantity = 0;
    for (auto od : salesData) {
        const QString& name = od->getFoodItem()->getName();
        const QDateTime& time = od->getAnswered();
        if (food_counts.find(name) == food_counts.end() && time <= rangeRight && time >= rangeLeft) {
            food_counts.insert(name, 0);
          }
        else {
            ++food_counts[name];
            if (food_counts[name] > max_quantity) max_quantity = food_counts[name];
          }
      }
    QHash<QString, unsigned>::const_iterator i = food_counts.constBegin();
    while (i != food_counts.constEnd()) {
        QBarSet *set = new QBarSet(i.key());
        *set << i.value();
        barSeries->append(set);
        ++i;
    }
    return max_quantity;
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
