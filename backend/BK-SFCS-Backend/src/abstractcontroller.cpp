#include "abstractcontroller.h"
#include "category.h"
#include "food.h"
AbstractController::AbstractController(QQmlApplicationEngine *eng, QObject *parent)
    : QObject(parent), p_engine(eng)
{
    // TODO: Load data right here
}
bool AbstractController::categoryIsVisible(const QString& cat_name) const {
    for (auto pcat : category_view_model) {
        Category& cat = *((Category *) pcat);
        if (cat_name == cat.getName())
            return cat.isVisible();
    }
    return false; // Category not found
}
void AbstractController::populateCategoryViewModel() {
    category_view_model.clear();
    // Run only once on startup
    category_view_model.append(new Category("Main dishes", QChar(127837), "#EF5350", "#EF5350"));
    category_view_model.append(new Category("Side dishes", QChar(129367), "#9CCC65", "#9CCC65"));
    category_view_model.append(new Category("Drinks", QChar(129380), "#03A9F4", "#03A9F4"));
    category_view_model.append(new Category("Desserts", QChar(127848), "#F48FB1", "#F48FB1"));
    category_view_model.append(new Category("Specials", QChar(127841), "#FFFF00", "#FFFF00"));

    p_engine->rootContext()->setContextProperty("categoryViewModel", QVariant::fromValue(category_view_model));
}
void AbstractController::populateMenuViewModel() {
    menu_view_model.clear(); // do not deallocate pointers - they're not dynamically allocated
    const QVector<QFood>& temp = *(current_stall.getMenu());
    for (auto qfood : temp) {
        if (categoryIsVisible(qfood.getType()))
            menu_view_model.append(&qfood);
    }

    p_engine->rootContext()->setContextProperty("menuViewModel", QVariant::fromValue(menu_view_model));
}
void AbstractController::repopulateStallViewModel() {
    // deallocate, since we'll freshly load from JSON
    for (auto p : stall_view_model) delete p;
    stall_view_model.clear();
    loadData();
}
QString AbstractController::getCurrentStallName() {
    return current_stall.getStallName();
}
QString AbstractController::getCurrentStallImagePath() {
    return current_stall.getImagePath();
}
bool AbstractController::setCurrentStall(const QString& name) {
    for (auto sptr : stall_view_model) {
        const Stall& stall = *((Stall *) sptr);
        if (stall.getStallName() == name) {
            current_stall = stall;
            return true;
        }
    }
    return false;
}
bool AbstractController::setCurrentStall(Stall* const sptr) {
    if (!sptr)
        return false;
    current_stall = *(sptr);
    return true;
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
    data_cursor.cdUp();
}
