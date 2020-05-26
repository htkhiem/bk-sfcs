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
}

void AbstractController::onTextMessageReceived(const QString& message) {
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

        }
      else { // failed

        }
    }
}
void AbstractController::onBinaryMessageReceived(const QByteArray& message) {
  bool result = (message.at(0) == '0') ? false : true;
  int sz1 = qFromLittleEndian<qint32_le>(message.mid(1, 4).data());
  QString request(message.mid(9, sz1));
  int sz2;
  QString text;
  if (result) {
      sz2 = qFromLittleEndian<qint32_le>(message.mid(5, 4).data());
      text = message.mid(9 + sz1, sz2);
    }
  if (request.left(2) == "IS") { // Stall image
      if (result) { // succeeded
          int idx = request.right(request.length() - 3).toInt();
          QDir data_cursor = this->getAppFolder();
          data_cursor.mkdir(((Stall *) stall_view_model[idx])->getStallName());
          data_cursor.cd(((Stall *) stall_view_model[idx])->getStallName());
          QFile stall_image(data_cursor.filePath(text));
          if (!stall_image.open(QIODevice::WriteOnly)) {
              throw runtime_error("Unable to write downloaded stall image to disk");
            }
          stall_image.write(message.right(message.size() - 9 - sz1 - sz2));
          ((Stall *) stall_view_model[idx])->setImagePath(text);
        }
      else { // failed

        }
    }
  else if (request.left(2) == "IM") { // Menu item image
      if (result) { // succeeded

        }
      else { // failed

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
QString AbstractController::getCurrentStallName() {
  return getCurrentStall()->getStallName();
}
QUrl AbstractController::getCurrentStallImagePath() {
  return getCurrentStall()->getImagePath();
}
void AbstractController::populateMenuViewModel() { // Offline
  for (auto ptr : menu_view_model) delete ptr;
  menu_view_model.clear();
  QVector<QFood>& temp = *(getCurrentStall()->getEditableMenu());
  for (QFood& qfood : temp) {
      if (categoryIsVisible(qfood.getType())) {
          QObject * qfoodptr = new QFood(qfood);
          ((QFood *) qfoodptr)->setValid(true);
          menu_view_model.append(qfoodptr);
        }
    }
  p_engine->rootContext()->setContextProperty("menuViewModel", QVariant::fromValue(menu_view_model));
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
    }
  else throw invalid_argument("Invalid QJsonObject passed to populateStallViewModel()");
}
bool AbstractController::setCurrentStall(int idx) {
  current_stall_idx = idx;
  return true;
}
void AbstractController::loadData() { // from server
  QDir data_cursor = this->getAppFolder();

  // Load stall menu and data
  web_socket.sendTextMessage("GS");
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

  p_engine->rootContext()->setContextProperty("stallViewModel", QVariant::fromValue(stall_view_model));
}
void AbstractController::saveData() {
  QDir data_cursor = this->getAppFolder();
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
