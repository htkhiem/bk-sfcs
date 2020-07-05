#ifndef SALES_H
#define SALES_H

#include <QObject>
#include "../../../backend/BK-SFCS-Backend/src/common.h"
#include "../../../backend/BK-SFCS-Backend/src/jsonable.h"
#include "../../../backend/BK-SFCS-Backend/src/orderinfo.h"

class Sales : public QObject {
    Q_OBJECT

    /* Fields */
    QList<QObject*> salesData;
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