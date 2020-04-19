#include "menu.h"

stall::stall()
{

}


void stall::getMenu(){   //Important for Display food

};
void stall::addFood(QFood item){   //Menu editing
this->menu.push_back(item);
};
void stall::removeFood(QFood item){ //Menu editing
QString name = item.getName();
for (int i = 0; i < this->menu.size();i++){
    if (this->menu[i].getName() == name)
        this->menu.erase(this->menu.begin()+i);
}
};

QString stall::getStallName(){
    return this->stallName;
};




void  stalllist::loadStall(const string filename){
    FILE* local;
    errno_t open_result = fopen_s(&local, filename.c_str(), "rb");

    if (open_result) return; // 0 if successful

    char buffer[8192];
    FileReadStream is(local, buffer, sizeof(buffer));

    Document food_json;
    food_json.ParseStream(is);

    // Check file validity
    assert(food_json.IsArray());

    QString stallName;
    QVector<QFood> foodlist;

    for (auto& v : food_json.GetArray()) {

        assert(v.HasMember("Stall name"));
        stallName = v["Stall name"].GetString();


        assert(v.HasMember("Servicing"));
        Value& srv = v["Servicing"];
        assert(srv.HasMember("records"));
        for (auto& r : srv["Menu"].GetArray()) {
            QFood f;

            assert(r.HasMember("Name"));
            assert(r.HasMember("Type"));
            assert(r.HasMember("Description"));
            assert(r.HasMember("Price"));
            f.name = r["name"].GetString();
            f.type = r["Type"].GetString();
            f.description = r["Description"].GetString();
            f.price = r["date"].GetInt();
            foodlist.push_back(f);
        }


    }
    fclose(local);

}
void  stalllist::writeStall(const string filename){
    FILE* local;
    errno_t open_result = fopen_s(&local, filename.c_str(), "wb");
    if (open_result) throw runtime_error("Failed to write data to local storage.");

    char buffer[8192];
    FileWriteStream os(local, buffer, sizeof(buffer));
    PrettyWriter<FileWriteStream> writer(os);

    writer.StartArray();
    for (auto p : stallList) {
        stall m = stallList.front();
        stallList.pop_front();
        writer.StartObject();

        writer.String("Stall name");
        writer.String(m.getStallName().toUtf8().constData());

        writer.String("Menu");
        writer.StartArray();
        for (auto f : m.menu) {
            writer.StartObject();

            writer.String("Name");
            writer.String(f.getName().toUtf8().constData());

            writer.String("type");
            writer.String(f.getType().toUtf8().constData());

            writer.String("Description");
            writer.String(f.getDescription().toUtf8().constData());

            writer.String("Price");
            writer.Double(f.getPrice());

            writer.EndObject();
        }
        writer.EndArray();
        writer.EndObject();

        writer.EndObject();
    }
    writer.EndArray();
    fclose(local);
}
