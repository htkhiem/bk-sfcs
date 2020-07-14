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

int Sales::drawTimeLineGraph(QAbstractSeries *response, QAbstractSeries *processing) {
    QXYSeries *responseXYSeries = static_cast<QXYSeries *>(response);
    QXYSeries *processingXYSeries = static_cast<QXYSeries *>(processing);
    responseXYSeries->clear();
    processingXYSeries->clear();

    QHash<QDateTime, int> response_time;
    QHash<QDateTime, int> processing_time;
    int max_time = 0;

    for (auto od : salesData) {
        const OrderStatus& status = od->getStatus();
        const QDateTime& time = od->getAnswered();
        const int& rtime = od->getResponseTime();
        const int& ptime = od->getProcessingTime();

        if (response_time.find(time) == response_time.end() && time <= rangeRight && time >= rangeLeft) {
            response_time.insert(time, rtime);
            if (response_time[time] > max_time) max_time = response_time[time];
        }

        if (processing_time.find(time) == processing_time.end() && status != OrderStatus::rejected
                && time <= rangeRight && time >= rangeLeft) {
            processing_time.insert(time, ptime);
            if (processing_time[time] > max_time) max_time = processing_time[time];
        }
    }

    QHash<QDateTime, int>::const_iterator i = response_time.constBegin();
    while (i != response_time.constEnd()) {
        responseXYSeries->append(i.key().toMSecsSinceEpoch(), i.value());
        ++i;
    }

    QHash<QDateTime, int>::const_iterator j = processing_time.constBegin();
    while (j != processing_time.constEnd()) {
        processingXYSeries->append(j.key().toMSecsSinceEpoch(), j.value());
        ++j;
    }

    return max_time;
}

unsigned Sales::drawRejectedBarGraph(QAbstractSeries *series) {
    QAbstractBarSeries *barSeries = static_cast<QAbstractBarSeries *>(series);
    barSeries->clear();

    QHash<QDate, unsigned> rejected_counts;
    unsigned max_order = 0;

    for (auto od : salesData) {
        const OrderStatus& status = od->getStatus();
        const QDateTime& time = od->getAnswered();
        const QDate& date = time.date();

        if (rejected_counts.find(date) == rejected_counts.end() && status == OrderStatus::rejected
                && time <= rangeRight && time >= rangeLeft) {
            rejected_counts.insert(date, 0);
          }
        else {
            ++rejected_counts[date];
            if (rejected_counts[date] > max_order) max_order = rejected_counts[date];
          }
      }

    QHash<QDate, unsigned>::const_iterator i = rejected_counts.constBegin();
    while (i != rejected_counts.constEnd()) {
        QBarSet *set = new QBarSet(i.key().toString());
        *set << i.value();
        barSeries->append(set);
        ++i;
    }

    return max_order;
}

void Sales::advancedExport() {

}
