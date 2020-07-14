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
    QDateTime rangeLeft = oldestDate, rangeRight = latestDate;
public:
    /* Constructor */
    Sales(QObject *parent = nullptr);
    void loadData(const QString& stall_name);
public slots:
    /* Functions */
    QString getRangeLeftStr() const;
    QString getRangeRightStr() const;
    void getOldestDate();
    void getLatestDate();
    void setStartRange(double pos);
    void setEndRange(double pos);
    unsigned drawQuantityBarGraph(QAbstractSeries *series);
    void drawTimeLineGraph(QAbstractSeries *series1, QAbstractSeries *series2);
    void drawRejectedBarGraph(QAbstractSeries *series);
    void advancedExport();
signals:
    void timeRangeChanged();
};

#endif // SALES_H
