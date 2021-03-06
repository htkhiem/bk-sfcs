#include "menu.h"

QVector<Stall> stallist;
Stall::Stall(QObject *parent) :
  Jsonable(parent)
{
}

Stall::Stall(const Stall& _stall, QObject *parent) :
  Jsonable(parent)
{
  this->menu = _stall.menu;
  stallName = _stall.stallName;
}

Stall& Stall::operator=(const Stall &) {
  return *this;
}
const QVector<QFood>* Stall::getMenu() const {   //Important for Display food
  return &menu;
}
QVector<QFood>* Stall::getEditableMenu() {   //Important for Display food
  return &menu;
}
bool Stall::addFood(QFood item){   //Menu editing
  menu.push_back(item);
  return 1;
}
bool Stall::removeFood(QFood item) { //Menu editing
  QString name = item.getName();
  for (int i = 0; i < menu.size();i++){
      if (menu[i].getName() == name){
          menu.erase(menu.begin()+i);
          return 1;
        }
    }
  return 0;
};

QString Stall::getStallName() const {
  return this->stallName;
}

void Stall::setStallName(const QString& name) {
  if (name.isEmpty()) throw invalid_argument("Stall name cannot be empty.");
  stallName = name;
}

QString Stall::getImageName() const
{
  return image_name;
}
void Stall::setImageName(const QString &name)
{
  image_name = name;
}

void Stall::read(const QJsonObject &json){
  if (json.contains("stall_name") && json["stall_name"].isString())
    stallName = json["stall_name"].toString();
  if (json.contains("stall_password") && json["stall_password"].isString())
    password = json["stall_password"].toString();
  if (json.contains("stall_mgmt_password") && json["stall_mgmt_password"].isString())
    mgmt_password = json["stall_mgmt_password"].toString();
  if (json.contains("image_path") && json["image_path"].isString())
    image_name = json["image_path"].toString();


  if (json.contains("menu") && json["menu"].isArray()) {
      QJsonArray menuArr = json["menu"].toArray();
      menu.clear();
      menu.reserve(menuArr.size());
      for(int i = 0; i < menuArr.size(); ++i){
          QFood temp;
          temp.read(menuArr[i].toObject());
          menu.append(temp);
        }
    }
}

void Stall::write(QJsonObject &json) const {
  json["stall_name"] = stallName;
  json["stall_password"] = password;
  json["stall_mgmt_password"] = mgmt_password;
  json["image_path"] = image_name;
  QJsonArray menuArr;
  for (const QFood &item : menu) {
      QJsonObject temp;
      item.write(temp);
      menuArr.append(temp);
    }
  json["menu"] = menuArr;
}

QString Stall::getPassword() const {
  return this->password;
}

void Stall::setPassword(QString password){
  this->password = password;
}

QString Stall::getMgmtPassword() const {
  return this->mgmt_password;
}

void Stall::setMgmtPassword(QString mgmt_password){
  this->mgmt_password = mgmt_password;
}
