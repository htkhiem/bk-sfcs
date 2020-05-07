#include "controller.h"

void Controller::run() {
    cout << "BK-SFCS ADMINISTRATIVE CONTROL PANEL\n";
    emit finished();
}

Controller::Controller(QObject *parent) : QObject(parent)
{

}

size_t Controller::DisplayStallList() {

}

void Controller::RegisterStall() {

}

void Controller::RemoveStall() {

}

void Controller::Login() {

}

void Controller::Logout() {

}

void Controller::AddFoodItem() {

}

void Controller::RemoveFoodItem() {

}

void Controller::EditFoodItem() {

}

void Controller::WriteData() {
    QDir data_cursor = QDir::current();
    data_cursor.mkdir("sfcs_data");
    data_cursor.cd("sfcs_data");

    // Write stall menu and data
    for (auto ptr : stall_db) {
        Stall& stall = *((Stall* )ptr);
        data_cursor.mkdir(stall.getStallName());
        data_cursor.cd(stall.getStallName());
        QFile stall_data_file(data_cursor.filePath(stall.getStallName() + QString(".json")));
        if (!stall_data_file.open(QIODevice::WriteOnly)) {
            throw runtime_error(
                        string("Cannot write data file for stall: ")
                        + stall.getStallName().toStdString());
        }
        QJsonObject stall_data_json_obj;
        stall.write(stall_data_json_obj);
        QJsonDocument stall_data_json_doc(stall_data_json_obj);
        stall_data_file.write(stall_data_json_doc.toJson());
        stall_data_file.close();
        data_cursor.cdUp();
    }
    // TODO: logging
    data_cursor.cdUp();
}

void Controller::ReadData() {
    QDir data_cursor = QDir::current();
    if (!data_cursor.cd("sfcs_data")) {
        throw runtime_error("Data folder not found. A blank folder will be created after this run.");
    }

    // Load stall menu and data
    data_cursor.setFilter(QDir::Dirs | QDir::NoDotAndDotDot);
    QStringList stall_dirs = data_cursor.entryList();
    for (auto qstr : stall_dirs) {
        data_cursor.cd(qstr);
        QFile stall_data_file(data_cursor.filePath(qstr + QString(".json")));
         if (!stall_data_file.open(QIODevice::ReadOnly)) {
            throw runtime_error("Cannot read data file: " + qstr.toStdString());
         }
         QJsonDocument stall_data_json_doc(QJsonDocument::fromJson(stall_data_file.readAll()));
         Stall* stall = new Stall();
         stall->read(stall_data_json_doc.object());
         stall_db.append(stall);
         stall_data_file.close();
         data_cursor.cdUp();
    }
    // TODO: Load logs
    data_cursor.cdUp();
}
