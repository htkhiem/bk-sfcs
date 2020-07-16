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
  oldestDate.fromSecsSinceEpoch(oldestDate.toSecsSinceEpoch() / 86400 * 86400);
  rangeLeft = oldestDate;
  emit timeRangeChanged();
}

void Sales::getLatestDate() {
    if (salesData.last()->getStatus() == OrderStatus::rejected)
        latestDate = salesData.last()->getAnswered();
    else
        latestDate = salesData.last()->getFinished();
    latestDate.fromSecsSinceEpoch(latestDate.toSecsSinceEpoch() / 86400 * 86400 + 86400);
    rangeRight = latestDate;
    emit timeRangeChanged();
}

unsigned Sales::getRangeLength() const
{
    return rangeLeft.daysTo(rangeRight);
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
double Sales::drawTimeLineGraph(QAbstractSeries *response, QAbstractSeries *processing) {
    QLineSeries *responseLineSeries = static_cast<QLineSeries *>(response);
    QLineSeries *processingLineSeries = static_cast<QLineSeries *>(processing);
    responseLineSeries->clear();
    processingLineSeries->clear();

    struct timeData {
        unsigned long long totalResponse = 0;
        unsigned long long totalProcessing = 0;
    };

    unsigned size = rangeLeft.date().daysTo(rangeRight.date()) + 1;
    QVector<timeData> timeLine(size, timeData());
    unsigned long long max_time = 0;

    //processing doesn't include rejected orders
    for (auto od : salesData) {
        const unsigned long long& od_response = od->getResponseTime();
        const unsigned long long& od_processing = od->getProcessingTime();
        const QDateTime& od_time = od->getAnswered();
        unsigned index = rangeLeft.date().daysTo(od_time.date());

        if (od_time <= rangeRight && od_time >= rangeLeft) {
            timeLine[index].totalResponse += od_response;
            timeLine[index].totalProcessing += od_processing;
        }
    }

    for (unsigned i = 0; i < size; i++) {
        if (timeLine[i].totalResponse > max_time) max_time = timeLine[i].totalResponse;
        if (timeLine[i].totalProcessing > max_time) max_time = timeLine[i].totalProcessing;
    }

    for (unsigned i = 0; i < size; i++) {
        responseLineSeries->append(i, timeLine[i].totalResponse / (double) 60000);
        processingLineSeries->append(i, timeLine[i].totalProcessing / (double) 60000);
    }

    return max_time / (double) 60000 * 1.25;
}

unsigned Sales::drawRejectedBarGraph(QAbstractSeries *series) {
    QAbstractBarSeries *barSeries = static_cast<QAbstractBarSeries *>(series);
    barSeries->clear();

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

void Sales::advancedExport(bool rep_pro_time, bool quantity, bool rejected, QUrl dir) {


    QFile export_file("export.csv");
    QTextStream stream(&export_file);

    stream << "Order Item,Order Time,";
    if (rep_pro_time) stream << "Response Time,Processing Time,";
    if (quantity) stream << "Quantity,";
    if (rejected) stream << "Rejected Orders";
    stream << endl;

    if (export_file.open(QIODevice::WriteOnly)) {
        for (auto od : salesData) {
            stream << od->getItemName() << ",";
            stream << od->getAnswered().toString() << ",";
            if (rep_pro_time) stream << od->getResponseTime() << "," << od->getProcessingTime() << ",";
            if (quantity) stream << od->getQuantity() << ",";
            if (rejected) stream << od->getStatus();
            stream << endl;
        }
    }

    export_file.close();
}
