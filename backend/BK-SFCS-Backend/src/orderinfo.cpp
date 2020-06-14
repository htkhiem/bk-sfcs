#include "orderinfo.h"
int OrderInfo::getKiosk() const
{
    return kiosk;
}

void OrderInfo::setKiosk(int value)
{
    kiosk = value;
}

int OrderInfo::getStall() const
{
    return stall;
}

void OrderInfo::setStall(int value)
{
    stall = value;
}

int OrderInfo::getFoodIdx() const
{
  return food_idx;
}

void OrderInfo::setFoodIdx(int value)
{
  food_idx = value;
}

OrderInfo::OrderInfo(QObject *parent) :
  Jsonable(parent), kiosk(-1), stall(-1)
{


}
OrderStatus OrderInfo::getStatus() const {
    return this->status;
}
void OrderInfo::setStatus(OrderStatus _status) {
  this->status = _status;
  if(_status == OrderStatus::processing) {
      this->time_answered = QDateTime::currentDateTime();
    }
  if(_status == OrderStatus::finished) {
      this->time_finished = QDateTime::currentDateTime();
    }
  if(_status == OrderStatus::rejected) {
      this->time_answered = QDateTime::currentDateTime();
      this->time_finished = QDateTime::currentDateTime();
    }
}
int OrderInfo::getQuantity() const {
  return this->quantity;
}
void OrderInfo::setQuantity(int quantity) {
  if (quantity <= 0) throw std::invalid_argument( "Quantity must not be negative or zero" );
  this->quantity = quantity;
}
void OrderInfo::setSlipNumber(int _number) {
    this->slip_number = _number;
}
int OrderInfo::getSlipNumber() const {
    return this->slip_number;
}
double OrderInfo::getTotal() const {
  return (this->food.getPrice() * this->quantity);
}
QDateTime OrderInfo::getReceived() const {
  return this->time_received;
}
void OrderInfo::setReceived() {
  this->time_received = QDateTime::currentDateTime();
}
QDateTime OrderInfo::getAnswered() const {
  return this->time_answered;
}
void OrderInfo::setAnswered(bool reject) {
  this->time_answered = QDateTime::currentDateTime();
  this->status = reject ? rejected : processing;
}
QDateTime OrderInfo::getFinished() const {
  return this->time_finished;
}
void OrderInfo::setFinished() {
  this->time_finished = QDateTime::currentDateTime();
}
int OrderInfo::getResponseTime() const {
  return this->time_received.time().secsTo(this->time_answered.time());
}
int OrderInfo::getProcessingTime() const {
  return this->time_answered.time().secsTo(this->time_finished.time());
}
void OrderInfo::read(const QJsonObject &json) {

  food.read(json["order"].toObject());
  QJsonObject temp = json["order"].toObject();
  if (temp.contains("quantity") && temp["quantity"].isDouble())
    quantity= temp["quantity"].toInt();
  if (temp.contains("food_idx") && temp["food_idx"].isDouble())
    quantity= temp["food_idx"].toInt();
  if (temp.contains("slip_number") && temp["slip_number"].isDouble())
      slip_number= temp["slip_number"].toInt();
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
  temp["slip_number"] = slip_number;
  temp["food_idx"] = food_idx;
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
const QFood * OrderInfo::getFoodItem() const {
  return &food;
}
void OrderInfo::setFoodItem(const QFood& _food) {
  food = _food;
}
QString OrderInfo::getItemName() const {
  return food.getName();
}
QString OrderInfo::getImageName() const {
  return food.getImageName();
}
