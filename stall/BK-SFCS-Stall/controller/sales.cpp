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
  rangeLeft = oldestDate;
  emit timeRangeChanged();
}

void Sales::getLatestDate() {
    if (salesData.last()->getStatus() == OrderStatus::rejected)
        latestDate = salesData.last()->getAnswered();
    else
        latestDate = salesData.last()->getFinished();
    latestDate.fromSecsSinceEpoch(latestDate.toSecsSinceEpoch() % 86400 + 86400);
    rangeRight = latestDate;
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
        const QDateTime& od_time = od->getAnswered();

        if (food_counts.find(name) == food_counts.end() && od_time <= rangeRight && od_time >= rangeLeft) {
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

    int max_time = 0;

    return max_time;
}

unsigned Sales::drawRejectedBarGraph(QAbstractSeries *series) {
    QAbstractBarSeries *barSeries = static_cast<QAbstractBarSeries *>(series);
    barSeries->clear();

    qDebug() << rangeLeft;
    qDebug() << rangeRight;
    unsigned size = rangeLeft.date().daysTo(rangeRight.date()) + 1;
    QVector<unsigned> rejected(size, 0);
    unsigned max_order = 0;

    for (auto od : salesData) {
        const OrderStatus& od_status = od->getStatus();
        const QDateTime& od_time = od->getAnswered();
        unsigned index = rangeLeft.date().daysTo(od_time.date());

        if (od_status == OrderStatus::rejected && od_time <= rangeRight && od_time >= rangeLeft) {
            rejected[index]++;
        }
    }

    for (unsigned i = 0; i < size; i++) {
        if (rejected[i] > max_order) max_order = rejected[i];
    }

    for (unsigned i = 0; i < size; i++) {
        QBarSet *set = new QBarSet(rangeLeft.date().addDays(i).toString());
        *set << rejected[i];
        barSeries->append(set);
    }

    return max_order;
}

void Sales::advancedExport() {

}
