#include "food.h"

QString QFood::getName(){
    return this->name;
};
QString QFood::getType(){
    return this->type;
};
QString QFood::getDescription(){
    return this->description;
};
double QFood::getPrice(){
    return this->price;
};
bool QFood::isSelected(){
    return this->select;
};
void QFood::setSelected(bool _sel){
    this->select = _sel;
};
