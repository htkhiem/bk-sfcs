#include "food.h"
QFood::QFood(const QFood &_food){
    name = _food.name;
    price = _food.price;
    description = _food.description;
    select = _food.select;
}
QFood& QFood::operator=(const QFood &){
    return *this;
}
QFood::QFood(){}
QString QFood::getName()const{
    return this->name;
};
void QFood::setName(QString name){
    this->name = name;
};
QString QFood::getType()const{
    return this->type;
};
void QFood::setType(QString type){
    this->type = type;
};
QString QFood::getDescription()const{
    return this->description;
};
void QFood::setDescription(QString des){
    this->description = des;
};
double QFood::getPrice()const{
    return this->price;
};
void QFood::setPrice(double price){
    this->price = price;
};
bool QFood::isSelected()const{
    return this->select;
};
void QFood::setSelected(bool _sel){
    this->select = _sel;
};
