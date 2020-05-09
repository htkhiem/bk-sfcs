#include "abstractcontroller.h"

AbstractController::AbstractController(QQmlApplicationEngine *eng, QObject *parent)
    : QObject(parent), p_engine(eng)
{
    // TODO: Load data right here
}
void AbstractController::populateCategoryViewModel() {

}
void AbstractController::populateMenuViewModel() {

}
void AbstractController::populateStallViewModel() {

}
QString AbstractController::getCurrentStallName() {

}
QString AbstractController::getCurrentStallImagePath() {

}
bool AbstractController::setCurrentStall(const QString& name) {

}
void AbstractController::loadData() {
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
         stall_view_model.append(stall);
         stall_data_file.close();
         data_cursor.cdUp();
    }
    // TODO: Load logs
    data_cursor.cdUp();
}
void AbstractController::saveData() {
    QDir data_cursor = QDir::current();
    data_cursor.cd("../../");
    data_cursor.mkdir("sfcs_data");
    data_cursor.cd("sfcs_data");

    // Write stall menu and data
    for (auto ptr : stall_view_model) {
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
