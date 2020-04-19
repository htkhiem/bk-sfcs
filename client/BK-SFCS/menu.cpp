#include "menu.h"

QVector<Stall> stallist;
Stall::Stall(){
}

Stall::Stall(const Stall& _stall){
    this->menu = _stall.menu;
    stallName = _stall.stallName;
}

Stall& Stall::operator=(const Stall &){
    return *this;
};
void Stall::getMenu() const{   //Important for Display food

};
bool Stall::addFood(QFood item){   //Menu editing
menu.push_back(item);
return 1;
};
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
};



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


        Value& srv = v["Servicing"];
        for (auto& r :srv["Menu"].GetArray()) {
            QFood f;

            assert(r.HasMember("Name"));
            assert(r.HasMember("Type"));
            assert(r.HasMember("Description"));
            assert(r.HasMember("Price"));
            f.name = r["name"].GetString();
            f.type = r["Type"].GetString();
            f.description = r["Description"].GetString();
            f.price = r["date"].GetInt();

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

            writer.String("type");
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
