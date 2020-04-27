#ifndef ORDERINFO_H
#define ORDERINFO_H

#include "common.h"
#include"food.h"
enum class OrderStatus{waiting,processing,finished,rejected};
//#include "../../backend/orderinfo.h"
class OrderInfo : public QObject
{
    Q_OBJECT
    size_t timestamp;   //time_t?
    OrderStatus status;
    QFood food;
    int quantity;

public:
    OrderInfo(QObject *parent = nullptr);

    bool checkWaiting();
    OrderStatus checkStatus();
    int setStatus(OrderStatus _status);
    size_t getTimeStamp();
    size_t setTimeStamp(size_t _time);
    double getTotal();
    int getQuantity();
    int setQuantity();
};
QVector<OrderInfo> waitList;
#endif // ORDERINFO_H
