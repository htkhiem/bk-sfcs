#include "food.h"

QString QFood::getName(){
    return this->name;
};
void QFood::setName(QString name){
    this->name = name;
};
QString QFood::getType(){
    return this->type;
};
void QFood::setType(QString type){
    this->type = type;
};
QString QFood::getDescription(){
    return this->description;
};
void QFood::setDescription(QString des){
    this->description = des;
};
double QFood::getPrice(){
    return this->price;
};
void QFood::setPrice(double price){
    this->price = price;
};
bool QFood::isSelected(){
    return this->select;
};
void QFood::setSelected(bool _sel){
    this->select = _sel;
};
