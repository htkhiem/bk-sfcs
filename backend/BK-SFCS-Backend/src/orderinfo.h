#ifndef ORDERINFO_H
#define ORDERINFO_H

#include "common.h"
#include "food.h"
#include "jsonable.h"
#include <time.h>
enum OrderStatus { waiting, processing, finished, rejected };



class OrderInfo : public Jsonable {
  Q_OBJECT
  OrderStatus status;
  QFood food;
  int quantity;
  QDateTime time_received;
  QDateTime time_answered;
  QDateTime time_finished;
public:
  
  /**
   * Basic constructor.
   * @param parent Pointer to parent QObject, if any.
   */
  OrderInfo(QObject *parent = nullptr);

  /** Basic getters/setters */
  OrderStatus getStatus();
  void setStatus(OrderStatus _status);
  double getTotal();
  int getQuantity();
  void setQuantity(int quantity);
  QDateTime getReceived();
  void setReceived();
  QDateTime getAnswered();
  void setAnswered();
  QDateTime getFinished();
  void setFinished();
  int getResponseTime();
  int getProcessingTime();
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
};

#endif // ORDERINFO_H
