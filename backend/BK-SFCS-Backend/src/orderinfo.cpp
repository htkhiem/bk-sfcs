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

}
void OrderInfo::write(QJsonObject &json) const{

}
