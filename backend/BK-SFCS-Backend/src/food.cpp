#include "food.h"
QFood::QFood(QObject *parent) :
Jsonable(parent) {}
QFood::QFood(const QFood &_food, QObject *parent) :
    Jsonable(parent)
{
    name = _food.name;
    price = _food.price;
    description = _food.description;
}
QFood& QFood::operator=(const QFood &){
    return *this;
}
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

