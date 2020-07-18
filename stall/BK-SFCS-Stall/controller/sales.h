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
    bool rep_pro_time = true, quantity = true, rejected = true;
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
    unsigned getRangeLength() const;
    void setStartRange(double pos);
    void setEndRange(double pos);
    unsigned drawQuantityBarGraph(QAbstractSeries *series);
    double drawTimeLineGraph(QAbstractSeries *series1, QAbstractSeries *series2);
    unsigned drawRejectedBarGraph(QAbstractSeries *series);
    void setBool(bool option1, bool option2, bool option3);
    void advancedExport(bool rep_pro_time, bool quantity, bool rejected, QUrl dir);
signals:
    void timeRangeChanged();
};

#endif // SALES_H
