#ifndef SALES_H
#define SALES_H

#include <QObject>
#include "common.h"
#include "jsonable.h"
#include "orderinfo.h"

class sales : public Jsonable {
    Q_OBJECT

    /* Fields */
    QList<OrderInfo> salesData;
    bool revenue, quantity, response, rejectedOrder;
    QDateTime oldestDate;
    QDateTime latestDate;

public:
    /* Constructor */
    sales(QObject *parent = nullptr);

    /* Functions */
    double getRevenue();
    void updateDate(QDateTime date);
    QBarSeries drawRevenueBarGraph();
    QBarSeries drawQuantityBarGraph();
    QLineSeries drawTimeLineGraph();
    QBarSeries drawRejectedBarGraph();
    void advancedExport(bool revenue, bool quantity, bool response, bool rejectedOrder);
};

#endif // SALES_H
