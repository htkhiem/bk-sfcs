#ifndef ORDERINFO_H
#define ORDERINFO_H

#include "common.h"
#include "food.h"
#include "jsonable.h"
enum OrderStatus { waiting, processing, finished, rejected };

class OrderInfo : public Jsonable {
  Q_OBJECT
  Q_PROPERTY(int quantity READ getQuantity)
  Q_PROPERTY(QString itemName READ getItemName)
  Q_PROPERTY(double total READ getTotal)

  OrderStatus status;
  QFood food;
  int quantity;
  QDateTime time_received;
  QDateTime time_answered;
  QDateTime time_finished;
  int kiosk;
  int stall;
public:
  
  /**
   * Basic constructor.
   * @param parent Pointer to parent QObject, if any.
   */
  OrderInfo(QObject *parent = nullptr);

  /** Basic getters/setters */
  OrderStatus getStatus() const;
  void setStatus(OrderStatus _status);
  const QFood * getFoodItem() const;
  void setFoodItem(const QFood& _food);
  void setQuantity(int quantity);
  QDateTime getReceived() const;
  void setReceived();
  QDateTime getAnswered() const;
  void setAnswered(bool reject = false);
  QDateTime getFinished() const;
  void setFinished();
  int getResponseTime() const;
  int getProcessingTime() const;
  /**
   * Read from a JSON object from disk.
   * @param json JSON object to read from.
   */
  void read(const QJsonObject &json);
  
  /**
   * Write to a JSON object for writing to file on disk.
   * @param json JSON object to write to.
   */
  void write(QJsonObject &json) const;
  int getKiosk() const;
  void setKiosk(int value);

  int getStall() const;
  void setStall(int value);

public slots:
  int getQuantity() const;
  QString getItemName() const;
  double getTotal() const;
  QString getImageName() const;
};

#endif // ORDERINFO_H
