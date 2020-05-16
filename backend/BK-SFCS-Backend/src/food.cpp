#include "food.h"
QFood::QFood(QObject *parent) :
  Jsonable(parent), type("Main dishes"), price(0), is_OOS(false), is_valid(true) {}
QFood::QFood(const QFood &_food, QObject *parent) :
  Jsonable(parent)
{
  name = _food.name;
  price = _food.price;
  description = _food.description;
  type = _food.type;
  image_name = _food.image_name;
  estimated_time = _food.estimated_time;
  is_OOS = _food.is_OOS;
}
QFood& QFood::operator=(const QFood & _food){
  name = _food.name;
  price = _food.price;
  description = _food.description;
  type = _food.type;
  image_name = _food.image_name;
  estimated_time = _food.estimated_time;
  is_OOS = _food.is_OOS;
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
void QFood::setName(const QString& name) {
  this->name = name;
};
QString QFood::getType() const {
  return this->type;
};
void QFood::setType(const QString& type) {
  this->type = type;
};
QString QFood::getDescription() const {
  return this->description;
};
void QFood::setDescription(const QString& desc) {
  this->description = desc;
};
double QFood::getPrice()const{
  return this->price;
};
void QFood::setPrice(double price) {
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

void QFood::setTime(int _time){
     estimated_time = _time;

}
int QFood::getTime(){
     return estimated_time;
}
bool QFood::isValid() {
  return is_valid;
}
void QFood::setValid(bool valid) {
  is_valid = valid;
}
