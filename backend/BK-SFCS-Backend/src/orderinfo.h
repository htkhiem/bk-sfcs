#ifndef ORDERINFO_H
#define ORDERINFO_H

#include "common.h"
#include "food.h"
#include "jsonable.h"
#include <chrono>
enum class OrderStatus { waiting, processing, finished, rejected };

class Timer{
public:
    std::chrono::high_resolution_clock::time_point start;
    std::chrono::duration<double> duration;
};

class OrderInfo : public Jsonable {
  Q_OBJECT
  size_t timestamp; // time_t?
  OrderStatus status;
  QFood food;
  int quantity;
  Timer received;
  Timer accepted;
public:
  
  /**
   * Basic constructor.
   * @param parent Pointer to parent QObject, if any.
   */
  OrderInfo(QObject *parent = nullptr);

  /** Basic getters/setters */
  void setReceived();
  void getReceived();
  void setAccepted();
  void getAccepted();
  OrderStatus checkStatus();
  void setStatus(OrderStatus _status);
  size_t getTimeStamp();
  void setTimeStamp(size_t _time);
  double getTotal();
  int getQuantity();
  void setQuantity(int);
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
