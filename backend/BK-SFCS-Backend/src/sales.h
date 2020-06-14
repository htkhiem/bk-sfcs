#ifndef SALES_H
#define SALES_H

#include <QObject>
#include "common.h"
#include "jsonable.h"
#include "orderinfo.h"

class sales : public Jsonable {
    Q_OBJECT

    /* Fields */
    QVector<OrderInfo> salesData;
    bool revenue, quantity, response, rejectedOrder;
    QDateTime oldestDate;
    QDateTime latestDate;

public:
    /* Constructor */
    sales(QObject *parent = nullptr);

    /* Functions */
    double getRevenue(QDateTime date);
    void updateOldestDate(QDateTime date);
    void updateLatestDate(QDateTime date);
    QBarSeries drawRevenueBarGraph();
    QBarSeries drawQuantityBarGraph();
    QLineSeries drawTimeLineGraph();
    QBarSeries drawRejectedBarGraph();
    void advancedExport();
};

#endif // SALES_H
