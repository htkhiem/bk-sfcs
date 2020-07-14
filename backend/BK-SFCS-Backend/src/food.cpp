#include "food.h"
bool QFood::getMatching() const
{
  return matching;
}

void QFood::setMatching(bool value)
{
  matching = value;
}

int QFood::getIdx() const
{
    return idx;
}

void QFood::setIdx(int value)
{
    idx = value;
}

QFood::QFood(QObject *parent) :
    Jsonable(parent), type("Main dishes"), price(0), is_OOS(false), estimated_time(0), is_valid(false), matching(true), idx(0) {}
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
  matching = _food.matching;
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
}
QString QFood::getImageName() const
{
  return image_name;
}
void QFood::setImageName(const QString& name) {
  image_name = name;
}

QString QFood::getName() const {
  return this->name;
}
void QFood::setName(const QString& name) {
  this->name = name;
}
QString QFood::getType() const {
  return this->type;
}
void QFood::setType(const QString& type) {
  this->type = type;
}
QString QFood::getDescription() const {
  return this->description;
}
void QFood::setDescription(const QString& desc) {
  this->description = desc;
}
double QFood::getPrice()const{
  return this->price;
}
void QFood::setPrice(double price) {
  this->price = price;
}

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
  if (json.contains("oos") && json["oos"].isBool())
    is_OOS = json["oos"].toBool();
  setValid(true);
}

void QFood::write(QJsonObject &json) const {
  // Remove "THUMB_" from filenames (avoid loop with server)
  if (image_name.leftRef(6) == "THUMB_")
    json["image_path"] = image_name.right(image_name.length() - 6);
  else
    json["image_path"] = image_name;

  json["name"] = name;
  json["description"] = description;
  json["type"] = type;
  json["price"] = price;
  json["estimated_time"] = (double)estimated_time;
  json["oos"] = is_OOS;
}

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
