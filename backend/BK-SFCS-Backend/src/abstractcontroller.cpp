#include "abstractcontroller.h"
#include "category.h"
#include "food.h"
AbstractController::AbstractController(QQmlApplicationEngine *eng, const QString& name, QObject *parent)
    : QObject(parent), app_name(name), p_engine(eng), current_stall_idx(0)
{
    // Loads server URL from config file
    QDir data_cursor = this->getAppFolder();
    QFile server_conf(data_cursor.filePath("server.conf"));
    if (server_conf.exists()) {
        if (!server_conf.open(QIODevice::ReadOnly)) {
            throw runtime_error("Cannot read configuration file.");
        }
        server_url = QUrl(QString(server_conf.readAll()));
        server_conf.close();
    }
    else {
        if (!server_conf.open(QIODevice::WriteOnly)) {
            throw runtime_error("Cannot write initial configuration file.");
        }
        server_conf.write(QByteArray("ws://localhost:25678"));
        server_url = QUrl("ws://localhost:25678");
    }
    qDebug() << "Server set to " << server_url;
    connect(&web_socket, &QWebSocket::connected, this, &AbstractController::onConnected);
    connect(&web_socket, QOverload<QAbstractSocket::SocketError>::of(&QWebSocket::error),
            [=](QAbstractSocket::SocketError error){ qDebug() << "Error: " << (int) error << "."; });
    connect(&web_socket, &QWebSocket::disconnected, this, &AbstractController::closed);
    web_socket.open(QUrl(server_url));
}

void AbstractController::onConnected() {
    populateCategoryViewModel();
    qDebug() << "WebSocket connected to " << server_url;
    connect(&web_socket, &QWebSocket::textMessageReceived, this, &AbstractController::onTextMessageReceived);
    connect(&web_socket, &QWebSocket::binaryMessageReceived, this, &AbstractController::onBinaryMessageReceived);
    // Get self index
    web_socket.sendTextMessage("KX");
    // Automatically fetch stall list
    getStallList();
}

void AbstractController::onTextMessageReceived(const QString& message) {
    qDebug() << "Text message received: " << message.left(48) << " (...)";
    QStringRef result(&message, 0, 2);
    QStringRef target(&message, 3, 2);
    if (target == "GL") { // GetList of stalls
        if (result == "OK") { // succeeded
            QStringRef data(&message, 6, message.length() - 7);
            QJsonObject stall_list_json = QJsonDocument(QJsonDocument::fromJson(data.toUtf8())).object();
            populateStallViewModel(stall_list_json);
        }
        else { //failed
            throw runtime_error("Server-side error: stall data could not be sent.");
        }
    }
    else if (target == "GM") { // GetMenu, might be received without asking in case menu is updated
        if (result == "OK") { // succeeded
            int json_start_pos = message.indexOf("{");
            QStringRef data(&message, json_start_pos, message.length() - json_start_pos - 1);
            QJsonObject menu_json = QJsonDocument(QJsonDocument::fromJson(data.toUtf8())).object();
            populateMenuViewModel(menu_json);
        }
        else { // failed
            throw runtime_error("Server-side error: stall menu could not be sent.");
        }
    }
    else if (target == "KX") { // logically guaranteed to succeed
        QStringList tokens = message.split(' ', QString::SkipEmptyParts);
        setClientIdx(tokens[2].toInt());
        qDebug() << "Handshake complete";
    }
    else if (target == "OD") {
        parseRepliesToKiosk(message);
    }
    else {
        parseRepliesToStall(message);
    }
}
void AbstractController::onBinaryMessageReceived(const QByteArray& message) {
    qDebug() << "Binary message: " << message.left(16);
    int result = message.left(2).toInt();
    int sz1 = message.mid(2, 2).toInt();

    if (result) {
        int sz2 = message.mid(4, 4).toInt();
        QString request(message.mid(8, sz1));
        QString text(message.mid(8 + sz1, sz2));
        QStringList request_tokens = request.split(' ', QString::SkipEmptyParts);
        qDebug() << "Binary message decoded: " << result <<
                    "sz1 = " << sz1 << ", sz2 = " << sz2 << "Text: " << text << ", R: " << request_tokens[0];
        if (request_tokens[0] == "IS") { // Stall image
            saveStallImage(request_tokens[1].toInt(), text, message.right(message.size() - 8 - sz1 - sz2));
            emit stallImageChanged(request_tokens[1].toInt());
        }
        else if (request_tokens[0] == "IM") { // Menu item image
            int stall_idx = request_tokens[1].toInt();
            int item_idx = request_tokens[2].toInt();
            saveMenuItemImage(stall_idx, item_idx, text, message.right(message.size() - 8 - sz1 - sz2));
            emit itemImageChanged(stall_idx, item_idx);
        }
        else if (request_tokens[0] == "IP") { // Full-res Menu item image => just set target QFood to use this item instead
            int stall_idx = request_tokens[1].toInt();
            int item_idx = request_tokens[2].toInt();
            saveMenuItemImage(stall_idx, item_idx, text, message.right(message.size() - 8 - sz1 - sz2));
            emit itemImageChanged(stall_idx, item_idx); // Popup will also listen to this signal
          }
    }
}
void AbstractController::getStallList() {
    web_socket.sendTextMessage("GL");
}
void AbstractController::getStallImage(int idx) {
    QString message = "IS " + QString::number(idx);
    web_socket.sendTextMessage(message);
}
void AbstractController::getStallMenu(int idx) {
    QString message = "GM " + QString::number(idx);
    web_socket.sendTextMessage(message);
}
void AbstractController::getMenuItemImage(int stall_idx, int item_idx) {
    QString message = "IM " + QString::number(stall_idx) + " " + QString::number(item_idx);
    web_socket.sendTextMessage(message);
}

void AbstractController::saveMenuItemImage(int stall_idx, int item_idx, const QString &filename, const QByteArray &image)
{
    QDir data_cursor = this->getAppFolder();
    data_cursor.mkdir(((Stall *) stall_view_model[stall_idx])->getStallName());
    data_cursor.cd(((Stall *) stall_view_model[stall_idx])->getStallName());
    QFile item_image(data_cursor.filePath(filename));
    if (!item_image.open(QIODevice::WriteOnly)) {
        throw runtime_error("Unable to write downloaded item image to disk");
    }
    item_image.write(image);
    item_image.close();
    ((QFood *) menu_view_model[item_idx])->setImageName(filename);
}

bool AbstractController::categoryIsVisible(const QString& cat_name) const {
    for (auto pcat : category_view_model) {
        Category& cat = *((Category *) pcat);
        if (cat_name == cat.getName())
            return cat.isVisible();
    }
    return false; // Category not found
}

QDir AbstractController::getAppFolder() {
    QDir data_cursor = QDir::home();
    data_cursor.mkdir(app_name);
    data_cursor.cd(app_name);
    return data_cursor;
}
void AbstractController::populateCategoryViewModel() { // Offline
    category_view_model.clear();
    // Run only once on startup
    category_view_model.append(new Category("Main dishes", QChar(127837), "#EF5350", "#EF5350"));
    category_view_model.append(new Category("Side dishes", QChar(129367), "#9CCC65", "#9CCC65"));
    category_view_model.append(new Category("Drinks", QChar(129380), "#03A9F4", "#03A9F4"));
    category_view_model.append(new Category("Desserts", QChar(127848), "#F48FB1", "#F48FB1"));
    category_view_model.append(new Category("Specials", QChar(127841), "#FFFF00", "#FFFF00"));

    p_engine->rootContext()->setContextProperty("categoryViewModel", QVariant::fromValue(category_view_model));
}

Stall* AbstractController::getCurrentStall() {
    return (Stall *) (stall_view_model[current_stall_idx]);
}

int AbstractController::getCurrentStallIdx()
{
    return current_stall_idx;
}
QString AbstractController::getCurrentStallName() {
    return getCurrentStall()->getStallName();
}
QUrl AbstractController::getCurrentStallImagePath() {
    QDir cursor(getCurrentStallPath());
    return QUrl::fromLocalFile(cursor.filePath(getCurrentStall()->getImageName()));
}
void AbstractController::populateMenuViewModel(const QJsonObject& list_obj) {
    if (list_obj.contains("menu") && list_obj["menu"].isArray()) {
        QJsonArray menuArr = list_obj["menu"].toArray();
        for (auto ptr : menu_view_model) delete ptr;
        menu_view_model.clear();
        menu_view_model.reserve(menuArr.size());
        for (int i = 0; i < menuArr.size(); ++i) {
            QFood *temp = new QFood(); // Lite stall object, containing just name
            QJsonObject obj = menuArr[i].toObject();
            temp->read(obj);
            menu_view_model.append(temp);
        }
    }
    p_engine->rootContext()->setContextProperty("menuViewModel", QVariant::fromValue(menu_view_model));
    emit menuJsonUpdated();

    // Now we can request images
    for (int i = 0; i < menu_view_model.size(); ++i) {
        getMenuItemImage(current_stall_idx, i);
    }
}
void AbstractController::populateStallViewModel(const QJsonObject& list_obj) {
    // deallocate, since we'll freshly load from JSON
    if (list_obj.contains("stall_list") && list_obj["stall_list"].isArray()) {
        QJsonArray stallArr = list_obj["stall_list"].toArray();
        for (auto p : stall_view_model) delete p;
        stall_view_model.clear();
        stall_view_model.reserve(stallArr.size());
        for(int i = 0; i < stallArr.size(); ++i){
            Stall *temp = new Stall(); // Lite stall object, containing just name
            QJsonObject obj = stallArr[i].toObject();
            if (obj.contains("name") && obj["name"].isString())
                temp->setStallName(obj["name"].toString());
            stall_view_model.append(temp);
        }
        p_engine->rootContext()->setContextProperty("stallViewModel", QVariant::fromValue(stall_view_model));

        // Now query images for each of them
        for (int i = 0; i < stall_view_model.size(); ++i) {
            getStallImage(i);
        }
    }
    else throw invalid_argument("Invalid QJsonObject passed to populateStallViewModel()");
}

QUrl AbstractController::getStallImagePath(int idx)
{
    Stall * target = (Stall *) stall_view_model[idx];
    QString stall_name = target->getStallName();
    QDir cursor = getAppFolder();
    cursor.cd(stall_name);
    return QUrl::fromLocalFile(cursor.filePath(target->getImageName()));
}

QUrl AbstractController::getItemImagePath(int item_idx)
{
    QDir cursor = getAppFolder();
    cursor.cd(getCurrentStallName());
    QString filename = ((QFood *) menu_view_model[item_idx])->getImageName();
    return QUrl::fromLocalFile(cursor.filePath(filename));
}
bool AbstractController::setCurrentStallIdx(int idx) {
    if (idx < stall_view_model.size() && idx >= 0)
        current_stall_idx = idx;
    else throw range_error("Current stall index out of range.");
    return true;
}
int AbstractController::getClientIdx() const
{
    return client_idx;
}

void AbstractController::setClientIdx(int value)
{
    client_idx = value;
}

void AbstractController::saveStallImage(int idx, const QString& name, const QByteArray& data) {
    qDebug() << "Received image for stall index " << idx << ", name: " << name;
    QDir data_cursor = this->getAppFolder();
    data_cursor.mkdir(((Stall *) stall_view_model[idx])->getStallName());
    data_cursor.cd(((Stall *) stall_view_model[idx])->getStallName());
    QFile stall_image(data_cursor.filePath(name));
    if (!stall_image.open(QIODevice::WriteOnly)) {
        throw runtime_error("Unable to write downloaded stall image to disk");
    }
    stall_image.write(data);
    stall_image.close();
    ((Stall *) stall_view_model[idx])->setImageName(name);
}

QString AbstractController::getCurrentStallPath() {
    QDir result = getAppFolder();
    result.cd(getCurrentStallName());
    return result.path();
}
