#ifndef SALES_H
#define SALES_H

#include <QObject>
#include "../../../backend/BK-SFCS-Backend/src/common.h"
#include "../../../backend/BK-SFCS-Backend/src/jsonable.h"
#include "../../../backend/BK-SFCS-Backend/src/orderinfo.h"

class Sales : public QObject {
    Q_OBJECT

    /* Fields */
    QVector<OrderInfo*> salesData;
    QDateTime oldestDate, latestDate;
    QDateTime rangeLeft, rangeRight;
    void loadData();

public:
    /* Constructor */
    Sales(QObject *parent = nullptr);
public slots:
    /* Functions */
    void setStartRange();
    void setEndRange();
    void drawQuantityBarGraph(QAbstractSeries *series);
    void drawTimeLineGraph(QAbstractSeries *series1, QAbstractSeries *series2);
    void drawRejectedBarGraph(QAbstractSeries *series);
    void advancedExport();
};

#endif // SALES_H
