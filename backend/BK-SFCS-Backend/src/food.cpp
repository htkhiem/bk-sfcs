#include "food.h"
QFood::QFood(QObject *parent) :
  Jsonable(parent), type("Main dishes"), price(0), is_OOS(false) {}
QFood::QFood(const QFood &_food, QObject *parent) :
  Jsonable(parent)
{
  name = _food.name;
  price = _food.price;
  description = _food.description;
  type = _food.type;
  image_name = _food.image_name;
  is_OOS = _food.is_OOS;
}
QFood& QFood::operator=(const QFood &){
  return *this;
};
QUrl QFood::getImagePath(const QString &stall_name) const {
  QDir stall_dir = QDir::home();
  stall_dir.cd("sfcs_data");
  stall_dir.cd(stall_name);
  return QUrl::fromLocalFile(stall_dir.filePath(image_name));
};
void QFood::setImagePath(const QString &stall_name, const QUrl &imgpath){
  QDir stall_dir = QDir::home();
  stall_dir.cd("sfcs_data");
  stall_dir.cd(stall_name);
  QFile::copy(imgpath.path(), stall_dir.filePath(imgpath.fileName()));
  image_name = imgpath.fileName();
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

  if (json.contains("image_path") && json["image_path"].isString())
    image_name = json["image_path"].toString();
  if (json.contains("name") && json["name"].isString())
    name = json["name"].toString();
  if (json.contains("description") && json["description"].isString())
    description = json["description"].toString();
  if (json.contains("type") && json["type"].isString())
    type = json["type"].toString();
  if (json.contains("price") && json["price"].isDouble())
    price = json["price"].toDouble();
  if (json.contains("estimated_time") && json["estimated_time"].isDouble())
    estimated_time = (size_t)json["estimated_time"].toDouble();
};

void QFood::write(QJsonObject &json) const {
  json["image_path"] = image_name;
  json["name"] = name;
  json["description"] = description;
  json["type"] = type;
  json["price"] = price;
  json["estimated_time"] = (double)estimated_time;
};

bool QFood::isOOS() {
  return is_OOS;
}

void QFood::setOOS(bool oos) {
  is_OOS = oos;
}

void QFood::setTime(size_t _time){
     estimated_time = _time;

}
size_t QFood::getTime(){
     return estimated_time;
}
