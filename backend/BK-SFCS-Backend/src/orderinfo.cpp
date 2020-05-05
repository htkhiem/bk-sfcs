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
       this->received_start = std::chrono::high_resolution_clock::now();
    }
}
void OrderInfo::setReceived(){
    if(this->status == OrderStatus::processing || this->status == OrderStatus::rejected){
        auto received_finish = std::chrono::high_resolution_clock::now();
        this->received_duration = received_finish - this->received_start;
    }
}
void OrderInfo::getAccepted(){
    if(this->status == OrderStatus::processing){
       this->accepted_start = std::chrono::high_resolution_clock::now();
    }
}
void OrderInfo::setAccepted(){
    if(this->status == OrderStatus::finished){
        auto accepted_finish = std::chrono::high_resolution_clock::now();
        this->accepted_duration = accepted_finish - this->accepted_start;
    }
}
