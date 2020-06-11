#ifndef KIOSKCONTROLLER_H
#define KIOSKCONTROLLER_H

#include <QObject>
#include "../../backend/BK-SFCS-Backend/src/orderinfo.h"
#include "../../backend/BK-SFCS-Backend/src/abstractcontroller.h"

class KioskController : public AbstractController
{
    Q_OBJECT
    Q_PROPERTY(int currentStallIdx READ getCurrentStallIdx WRITE setCurrentStallIdx)
    OrderInfo current_order;
    int current_stall_idx;
public:
    explicit KioskController(QQmlApplicationEngine *eng, QObject *parent = nullptr);
public slots:
    int getCurrentStallIdx();
    void setCurrentStallIdx(int idx);
    void searchFilter(const QString& _input);
    void setOrderFoodItem(int idx);
    void setOrderQuantity(int qty);
    void setOrderMethod(int method); // TODO
    QString sendOrder();
    bool waitForResults(const QString& order_name);
signals:
};

#endif // KIOSKCONTROLLER_H
