#ifndef KIOSKCONTROLLER_H
#define KIOSKCONTROLLER_H

#include <QObject>
#include "../../backend/BK-SFCS-Backend/src/orderinfo.h"
#include "../../backend/BK-SFCS-Backend/src/abstractcontroller.h"

class KioskController : public AbstractController
{
  Q_OBJECT
  Q_PROPERTY(int currentOrderStatus READ getCurrentOrderStatus NOTIFY currentOrderStatusChanged)
  OrderInfo current_order;
  void parseRepliesToKiosk(const QString& message) override;
  void parseRepliesToStall(const QString& message) override;
  QTimer reconnection_timer;
  void startReconnectionLoop();
  void tryReconnect();
  void finishReconnection();
public:
  explicit KioskController(QQmlApplicationEngine *eng, QObject *parent = nullptr);
public slots:
  void initOrder(int idx);
  void getFullResItemImage(int idx);
  void searchFilter(const QString& _input = "");
  void setOrderFoodItem(int idx);
  void setOrderQuantity(int qty);
  void setOrderMethod(int method); // TODO
  void sendOrder();
  // Lite version of OrderStatus since it only handles three cases:
  // waiting, processing and rejected, which are 0 to 2 as int respectively.
  int getCurrentOrderStatus();

  signals:
  void currentOrderStatusChanged(int slip = -1);
  void connectionLost();
  void connectionBack();
};

#endif // KIOSKCONTROLLER_H
