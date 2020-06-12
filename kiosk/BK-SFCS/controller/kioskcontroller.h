#ifndef KIOSKCONTROLLER_H
#define KIOSKCONTROLLER_H

#include <QObject>
#include "../../backend/BK-SFCS-Backend/src/orderinfo.h"
#include "../../backend/BK-SFCS-Backend/src/abstractcontroller.h"

class KioskController : public AbstractController
{
  Q_OBJECT
  Q_PROPERTY(int currentStallIdx READ getCurrentStallIdx WRITE setCurrentStallIdx)
  Q_PROPERTY(int currentOrderStatus READ getCurrentOrderStatus NOTIFY currentOrderStatusChanged)
  OrderInfo current_order;
  int current_stall_idx;
  void parseOrderReply(const QString& message) override;
public:
  explicit KioskController(QQmlApplicationEngine *eng, QObject *parent = nullptr);
public slots:
  int getCurrentStallIdx();
  void setCurrentStallIdx(int idx);
  void searchFilter(const QString& _input);
  void setOrderFoodItem(int idx);
  void setOrderQuantity(int qty);
  void setOrderMethod(int method); // TODO
  void sendOrder();
  // Lite version of OrderStatus since it only handles three cases:
  // waiting, processing and rejected, which are 0 to 2 as int respectively.
  int getCurrentOrderStatus();

  signals:
  void currentOrderStatusChanged();
};

#endif // KIOSKCONTROLLER_H
