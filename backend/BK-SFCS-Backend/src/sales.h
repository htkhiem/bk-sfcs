#ifndef SALES_H
#define SALES_H

#include <QObject>
#include "common.h"
#include "jsonable.h"
#include "orderinfo.h"

class Sales : public QObject {
    Q_OBJECT

    /* Fields */
    QVector<OrderInfo> salesData;
    bool quantity, response, rejectedOrder;
    QDateTime oldestDate;
    QDateTime latestDate;

public:
    /* Constructor */
    Sales(QObject *parent = nullptr);

    /* Functions */
    void updateOldestDate(QDateTime date);
    void updateLatestDate(QDateTime date);
    QBarSeries drawQuantityBarGraph();
    QLineSeries drawTimeLineGraph();
    QBarSeries drawRejectedBarGraph();
    void advancedExport();
};

#endif // SALES_H
