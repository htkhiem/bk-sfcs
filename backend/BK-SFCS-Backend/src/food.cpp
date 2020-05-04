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
   if (name == NULL) throw std::invalid_argument( "Name must not be blank" );
   else this->name = name;
};
QString QFood::getType()const{
    return this->type;
};
void QFood::setType(QString type){
  if (type == NULL) throw std::invalid_argument( "Type must be within known ones" );
  else  this->type = type;
};
QString QFood::getDescription()const{
    return this->description;
};
void QFood::setDescription(QString des){
  if (des == NULL) throw std::invalid_argument( "No description recieved" );
   else this->description = des;
};
double QFood::getPrice()const{
    return this->price;
};
void QFood::setPrice(double price){
  if (price <= 0) throw std::invalid_argument( "Price must not be negative or zero" );
    this->price = price;
};

