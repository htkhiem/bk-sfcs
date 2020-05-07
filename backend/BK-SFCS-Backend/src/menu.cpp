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

Stall& Stall::operator=(const Stall &){
    return *this;
}
QVector<QFood> Stall::getMenu() const{   //Important for Display food
    return menu;
}
bool Stall::addFood(QFood item){   //Menu editing
menu.push_back(item);
return 1;
}
bool Stall::removeFood(QFood item){ //Menu editing
QString name = item.getName();
for (int i = 0; i < menu.size();i++){
    if (menu[i].getName() == name){
        menu.erase(menu.begin()+i);
        return 1;
    }
}
return 0;
};

QString Stall::getStallName(){
    return this->stallName;
}


QString Stall::getImagePath(){
    return this->imagePath;
}
void Stall::setImagePath(){

}

void Stall::write(QJsonObject &json) const{

}
void Stall::read(const QJsonObject &json){
    if (json.contains("stall name") && json["stall name"].isString())
        stallName = json["name"].toString();

    if (json.contains("image path") && json["image path"].isString())
        imagePath = json["image path"].toString();


    if (json.contains("menu") && json["menu"].isArray()) {
        QJsonArray menuArr = json["menu"].toArray();
        menu.clear();
        menu.reserve(menuArr.size());
    for(int i = 0; i < menuArr.size(); ++i){
        QFood temp;
           QJsonObject obj = menuArr[i].toObject();
        if (obj.contains("name") && obj["name"].isString())
            temp.name = obj["name"].toString();
        if (obj.contains("description") && obj["description"].isString())
            temp.description = obj["description"].toString();
        if (obj.contains("type") && obj["type"].isString())
            temp.type = obj["category"].toString();
        if (obj.contains("price") && obj["price"].isDouble())
            temp.price = obj["price"].toDouble();
        menu.push_back(temp);
        }
    }
}
