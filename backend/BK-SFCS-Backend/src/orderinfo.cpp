#include "orderinfo.h"
#include <chrono>
OrderInfo::OrderInfo(QObject *parent) :
  Jsonable(parent)
{


}
OrderStatus OrderInfo::getStatus(){
  return this->status;
}
void OrderInfo::setStatus(OrderStatus _status){
  this->status = _status;
  if(_status == OrderStatus::processing){
      this->time_answered = QDateTime::currentDateTime();
    }
  if(_status == OrderStatus::finished){
      this->time_finished = QDateTime::currentDateTime();
    }
  if(_status == OrderStatus::rejected){
      this->time_answered = QDateTime::currentDateTime();
      this->time_finished = QDateTime::currentDateTime();
    }
}
int OrderInfo::getQuantity(){
  return this->quantity;
}
void OrderInfo::setQuantity(int quantity){
  if (quantity <= 0) throw std::invalid_argument( "Quantity must not be negative or zero" );
  this->quantity = quantity;
}

void OrderInfo::setSlipNumber(int _number){
    this->slip_number = _number;
}
int OrderInfo::getSlipNumber(){
    return this->slip_number;
}
void OrderInfo::setOrderID(QString _id){
    this->orderID = _id;
}
QString OrderInfo::getOrderID(){
    return this->orderID;
}

double OrderInfo::getTotal(){
  return (this->food.getPrice() * this->quantity);
}

QDateTime OrderInfo::getReceived(){
  return this->time_received;
}
void OrderInfo::setReceived(){
  this->time_received = QDateTime::currentDateTime();
}
QDateTime OrderInfo::getAnswered(){
  return this->time_answered;
}
void OrderInfo::setAnswered(bool reject){
  this->time_answered = QDateTime::currentDateTime();
  this->status = reject ? rejected : processing;
}
QDateTime OrderInfo::getFinished(){
  return this->time_finished;
}
void OrderInfo::setFinished(){
  this->time_finished = QDateTime::currentDateTime();
}
int OrderInfo::getResponseTime(){
  return this->time_received.time().secsTo(this->time_answered.time());
}
int OrderInfo::getProcessingTime(){
  return this->time_answered.time().secsTo(this->time_finished.time());
}
void OrderInfo::read(const QJsonObject &json){
  food.read(json);
  if (json.contains("quantity") && json["quantity"].isDouble())
    quantity= json["quantity"].toInt();

  if (json.contains("orderID") && json["orderID"].isString())
      orderID = json["orderID"].toString();
  if (json.contains("slip_number") && json["slip_number"].isDouble())
      slip_number= json["slip_number"].toInt();
  if (json.contains("status") && json["status"].isDouble())
    {
      int ienum = json["status"].toInt();
      status = static_cast<OrderStatus>(ienum);
    }

  if (json.contains("time received") && json["time received"].isDouble())
    {
      if (status == OrderStatus::waiting) time_received = QDateTime::currentDateTime();
      else
        {
          int t_rcv = json["time received"].toInt();
          time_received = QDateTime::fromMSecsSinceEpoch(t_rcv);
        }
    }


  if (json.contains("time answered") && json["time answered"].isDouble())
    {
      int t_ans = json["time answered"].toInt();
      time_answered = QDateTime::fromMSecsSinceEpoch(t_ans);
    }

  if (json.contains("time finished") && json["time finished"].isDouble())
    {
      int t_fin = json["time finished"].toInt();
      time_finished = QDateTime::fromMSecsSinceEpoch(t_fin);
    }


}
void OrderInfo::write(QJsonObject &json) const {
  QJsonObject temp;
  food.write(temp);
  temp["quantity"] = quantity;
  temp["orderID"] = orderID;
  temp["slip_number"] = slip_number;
  json["order"] = temp;
  json["status"] = status;
  json["time received"] = time_received.toMSecsSinceEpoch();
  switch (status)
    {
    case OrderStatus::processing :
      {
        double t_ans = time_answered.toMSecsSinceEpoch();
        json["time answered"] = t_ans;
        break;
      }
    case OrderStatus::finished :
      {
        double t_fin = time_finished.toMSecsSinceEpoch();
        json["time finished"] = t_fin;
        break;
      }
    case OrderStatus::rejected :
      {
        double t_ans = time_answered.toMSecsSinceEpoch();
        json["time answered"] = t_ans;
        double t_fin = time_finished.toMSecsSinceEpoch();
        json["time rejected"] = t_fin;
        break;
      }
    case OrderStatus::waiting :
      {
        json["time answered"] = 0;
        json["time finished"] = 0;
      }
    }
}

void OrderInfo::readLog(const QJsonObject &json){

}
void OrderInfo::writeLog(int i,bool finished,const QString& stall_name) const{
    //Access order folder from specific stall
    QDir data_cursor = QDir::home();
    data_cursor.cd("sfcs_data/"+ stall_name +"/log");
    QFile order_file(data_cursor.filePath(orderID + QString(".json")));

    //Create a json object, write into it
    OrderInfo& order = *((OrderInfo*)i);
    if (finished) order.setStatus(OrderStatus::finished);
    else order.setStatus(OrderStatus::rejected);
    QJsonObject json;
    order.write(json);

    //Then write that json object into disk
    QJsonDocument order_json_log(json);
    order_file.write(order_json_log.toJson());
    order_file.close();
}


QFood * OrderInfo::getFoodItem() {
  return &food;
}
void OrderInfo::setFoodItem(const QFood& _food) {
  food = _food;
}
QString OrderInfo::getItemName() {
  return food.getName();
}
QUrl OrderInfo::getImagePath(const QString& stall_name) {
  return food.getImagePath(stall_name);
}
