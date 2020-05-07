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
};
QString QFood::getImagePath()const{
    return this->imagepath;
};
void QFood::setImagePath(QString imagepath){
  this->imagepath = imagepath;
};
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

void QFood::read(const QJsonObject &json){

      if (json.contains("image path") && json["image path"].isString())
          imagepath = json["image path"].toString();
      if (json.contains("name") && json["name"].isString())
              name = json["name"].toString();
      if (json.contains("description") && json["description"].isString())
              description = json["description"].toString();
      if (json.contains("type") && json["type"].isString())
              type = json["category"].toString();
      if (json.contains("price") && json["price"].isDouble())
              price = json["price"].toDouble();
};

void QFood::write(QJsonObject &json) const{
     json["image path"] = imagepath;
         json["name"] = name;
         json["description"] = description;
         json["type"] = type;
         json["price"] = price;
};
