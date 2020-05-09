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

double OrderInfo::getTotal(){
    return (this->food.price * this->quantity);
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
void OrderInfo::setAnswered(){
    this->time_answered = QDateTime::currentDateTime();
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
void OrderInfo::write(QJsonObject &json) const{

  QJsonObject temp;
  food.write(temp);
  temp["quantity"] = quantity;
  json["order:"] = temp;
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
      json["time finished"] = t_fin;
      break;
      }
  case OrderStatus::waiting :
      {
        json["time answered"] = 0;
        json["time finished"] = 0;
      }
    }
}
