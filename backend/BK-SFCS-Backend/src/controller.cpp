#include "controller.h"

void Controller::run() {
    cout << "BK-SFCS ADMINISTRATIVE CONTROL PANEL\n";
    emit finished();
}

Controller::Controller(QObject *parent) : QObject(parent), logged_in(false)
{
}

size_t Controller::DisplayStallList() {
    for (auto ptr : stall_db) {
        const Stall& stall = *((Stall*)ptr);
        cout << "\nName: " << stall.getStallName().toStdString() << '\n';
        cout << "\nMenu size: " << stall.getMenu().size() << '\n';
    }
    return stall_db.size();
}

void Controller::RegisterStall() {
    string buf;
    QString qbuf;
    Stall* stall = new Stall(nullptr);
    cout << "Name: ";
    getline(cin, buf);
    qbuf = QString::fromStdString(buf);
    for (int i = 0; i < stall_db.size(); ++i) {
        if (((Stall*)stall_db[i])->getStallName() == qbuf) {
            cout << "A stall with that name already exists!\n";
            return;
        }
    }

    stall->setStallName(QString::fromStdString(buf));
    // TODO: passwords
    cout<<"Add food?(Y/n): ";
    getline(cin, buf);
    while(buf=="Y"){
          QFood food;
          cout<<"Food name:";
          getline(cin,buf);
          food.setName(QString::fromStdString(buf));
          cout<<"Food description:";
          getline(cin,buf);
          food.setDescription(QString::fromStdString(buf));
          cout<<"Food type:";
          getline(cin,buf);
          food.setType(QString::fromStdString(buf));
          cout<<"Food price:";
          getline(cin,buf);
          food.setPrice(stod(buf));
          stall->addFood(food);
          cout<<"Would you like to add another item?(Y/n): ";
          getline(cin, buf);
    }
    stall_db.append(stall);
    cout << "Stall created.\n";
}

bool Controller::RemoveStall() {
    string buf;
    cout << "Name of stall to remove: ";
    getline(cin, buf);
    QString term = QString::fromStdString(buf);
    for (int i = 0; i < stall_db.size(); ++i) {
        if (((Stall*)stall_db[i])->getStallName() == term) {
            stall_db.removeAt(i);
            return true;
        }
    }
    return false;
}

int Controller::Login() {
    if (logged_in) return 2; // Already logged in
    string name, psw;
    cout << "Stall name: ";
    getline (cin, name);
    cout << "Password: ";
    getline(cin, psw);
    QString qname = QString::fromStdString(name);
    QString qpsw = QString::fromStdString(psw);
    for (int i = 0; i < stall_db.size(); ++i) {
        if (((Stall*)stall_db[i])->getStallName() == qname) {
            //if (((Stall*)stall_db[i])->getPassword() == qpsw) { // TODO here
                current_stall = *((Stall*)stall_db[i]);
                logged_in = true;
                return 0; // Success
            //}
            //return 1; // Wrong password
        }
    }
    return -1; // Stall not found
}

bool Controller::Logout() {
    if (!logged_in) return false;
    for (int i = 0; i < stall_db.size(); ++i) {
        if (((Stall*)stall_db[i])->getStallName() == current_stall.getStallName()) {
            *((Stall*)stall_db[i]) = current_stall;
            logged_in = false;
            break;
        }
    }
    // Blank out
    current_stall = Stall();
    return true;
}

void Controller::AddFoodItem() {

}

void Controller::RemoveFoodItem() {

}

void Controller::EditFoodItem() {

}

void Controller::WriteData() {
    QDir data_cursor = QDir::current();
    data_cursor.cd("../../");
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
    data_cursor.cd("../../");
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
