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
  Q_PROPERTY(QString orderID READ getOrderID WRITE setOrderID)
  Q_PROPERTY(QUrl imagePath READ getImagePath)
  QString orderID;
  int slip_number;
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
  QFood * getFoodItem();
  void setFoodItem(const QFood& _food);
  void setQuantity(int quantity);
  void setSlipNumber(int _number);
  void setOrderID(QString _id);
  QDateTime getReceived();
  void setReceived();
  QDateTime getAnswered();
  void setAnswered(bool _reject);
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

  /**
   * Read from a JSON object from disk.
   * @param json JSON object to read from.
   */
  void readLog(const QJsonObject &json);
  /**
   * Write to a file on disk used stall_name as path.
   * @param i: index of an order to write log.
   * @param finished: boolen to set status of that order in log
   */
  void writeLog(int i,bool finished,const QString& stall_name) const;

public slots:
  int getQuantity();
  int getSlipNumber();
  QString getOrderID();
  QString getItemName();
  double getTotal();
  QUrl getImagePath(const QString& stall_name);
};

#endif // ORDERINFO_H
