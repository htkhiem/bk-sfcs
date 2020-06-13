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
  OrderStatus status;
  QFood food;
  int quantity;
  QString orderID;
  int slip_number;
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
<<<<<<< HEAD
  QDateTime getReceived() const;
=======
  void setSlipNumber(int _number);
  void setOrderID(QString _id);
  QDateTime getReceived();
>>>>>>> 4778c87ba07fdb1776ffc405586cf50aa264a25a
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

  int getKiosk() const;
  void setKiosk(int value);

  int getStall() const;
  void setStall(int value);


public slots:
<<<<<<< HEAD
  int getQuantity() const;
  QString getItemName() const;
  double getTotal() const;
  QString getImageName() const;
=======
  int getQuantity();
  int getSlipNumber();
  QString getOrderID();
  QString getItemName();
  double getTotal();
  QUrl getImagePath(const QString& stall_name);
>>>>>>> 4778c87ba07fdb1776ffc405586cf50aa264a25a
};

#endif // ORDERINFO_H
