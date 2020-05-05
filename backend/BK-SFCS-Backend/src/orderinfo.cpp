#include "orderinfo.h"
#include <chrono>
OrderInfo::OrderInfo(QObject *parent) :
   Jsonable(parent)
{


}
OrderStatus OrderInfo::checkStatus(){
    return this->status;
}
void OrderInfo::setStatus(OrderStatus _status){
    this->status = _status;
}
void OrderInfo::getReceived(){
    if(this->status == OrderStatus::waiting){
       this->received.start = std::chrono::high_resolution_clock::now();
    }
}
void OrderInfo::setReceived(){
    if(this->status == OrderStatus::processing || this->status == OrderStatus::rejected){
        auto finish = std::chrono::high_resolution_clock::now();
        this->received.duration = finish - this->received.start;
    }
}
void OrderInfo::getAccepted(){
    if(this->status == OrderStatus::processing){
       this->accepted.start = std::chrono::high_resolution_clock::now();
    }
}
void OrderInfo::setAccepted(){
    if(this->status == OrderStatus::finished){
        auto finish = std::chrono::high_resolution_clock::now();
        this->accepted.duration = finish - this->accepted.start;
    }
}
size_t OrderInfo::getTimeStamp(){
   return this->timestamp;
}
void OrderInfo::setTimeStamp(size_t _time){
   this->timestamp = _time;
}
int OrderInfo::getQuantity(){
    return this->quantity;
}
void OrderInfo::setQuantity(int quantity){
    this->quantity = quantity;
}
