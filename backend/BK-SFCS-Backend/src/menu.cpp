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

void Stall::write(QJsonObject &json) const{
    json["stall name"] = stallName;
    json["image path"] = imagePath;
    QJsonArray menuArr;
    for (const QFood &items : menu) {
        QJsonObject temp;
        temp["name"] = items.name;
        temp["description"] = items.description;
        temp["type"] = items.type;
        temp["price"] = items.price;
        menuArr.append(temp);
    }
    json["menu"] = menuArr;
}
/*
void  loadStall(const string filename){
    FILE* local;
    local = fopen( filename.c_str(), "rb");



    char buffer[8192];
    FileReadStream is(local, buffer, sizeof(buffer));

    Document food_json;
    food_json.ParseStream(is);

    // Check file validity
    assert(food_json.IsArray());

    QString stallName;

    for (auto& v : food_json.GetArray()) {

        Stall stall;
        assert(v.HasMember("Stall name"));
        stall.stallName = v["Stall name"].GetString();

        assert(v.HasMember("Menu"));
        for (auto& x :v["Menu"].GetArray()) {
            QFood f;

            assert(x.HasMember("Name"));
            assert(x.HasMember("Type"));
            assert(x.HasMember("Description"));
            assert(x.HasMember("Price"));
            f.name = x["Name"].GetString();
            f.type = x["Type"].GetString();
            f.description = x["Description"].GetString();
            f.price = x["Price"].GetDouble();

            stall.menu.push_back(f);
        }
       stallist.push_back(stall);

    }
    fclose(local);

}
void writeStall(const string filename){
FILE* local;
   local=fopen(filename.c_str(), "wb");


    char buffer[8192];
    FileWriteStream os(local, buffer, sizeof(buffer));
    PrettyWriter<FileWriteStream> writer(os);
    QVectorIterator<Stall> i(stallist);
    writer.StartArray();

    while (i.hasNext()) {
        writer.StartObject();

        writer.String("Stall name");
        writer.String(stallist.data()->getStallName().toUtf8().constData());

        writer.String("Menu");
        writer.StartArray();

        QVectorIterator<QFood> j(stallist.data()->menu);
        while (j.hasNext()) {

            writer.StartObject();

            writer.String("Name");
            writer.String(stallist.data()->menu.data()->getName().toUtf8().constData());

            writer.String("Type");
            writer.String(stallist.data()->menu.data()->getType().toUtf8().constData());

            writer.String("Description");
            writer.String(stallist.data()->menu.data()->getDescription().toUtf8().constData());

            writer.String("Price");
            writer.Double(stallist.data()->menu.data()->getPrice());

            writer.EndObject();
            j.next();
        }
        writer.EndArray();
        writer.EndObject();

        i.next();
    }
    writer.EndArray();
    fclose(local);
}
*/
