#include "servercontroller.h"
#include "../../backend/BK-SFCS-Backend/src/menu.h"

ServerController::ServerController(QQmlApplicationEngine *eng, QObject *parent) :
  QObject(parent),
  web_socket_server(new QWebSocketServer(QStringLiteral("BK-SFCS Server"), QWebSocketServer::NonSecureMode, this)),
  app_name(web_socket_server->serverName()),
  p_engine(eng)
{
  // Loads server URL from config file
  QDir data_cursor = this->getAppFolder();
  QFile server_conf(data_cursor.filePath("server.conf"));
  bool result;
  if (server_conf.exists()) {
      if (!server_conf.open(QIODevice::ReadOnly)) {
          throw runtime_error("Cannot read configuration file.");
        }
      result = web_socket_server->listen(QHostAddress(QString(server_conf.readLine())),
                                         server_conf.readLine().toInt());
      server_conf.close();
    }
  else {
      qDebug() << "Creating new configuration file...";
      if (!server_conf.open(QIODevice::WriteOnly)) {
          throw runtime_error("Cannot write initial configuration file.");
        }
      server_conf.write(QByteArray("::1")); // defaults to localhost
      server_conf.write(QByteArray("25678"));
      result = web_socket_server->listen(QHostAddress("::1"), 25678);
    }
  if (result) {
      qDebug() << "BK-SFCS Server listening on " << web_socket_server->serverAddress()
               <<", port " << web_socket_server->serverPort();
      connect(web_socket_server, &QWebSocketServer::newConnection,
              this, &ServerController::onNewConnection);
      connect(web_socket_server, &QWebSocketServer::closed,
              this, &ServerController::closed);
    }
}

ServerController::~ServerController() {
  web_socket_server->close();
  qDeleteAll(clients.begin(), clients.end());
}

void ServerController::onNewConnection() {
  Client *client = new Client(web_socket_server->nextPendingConnection());
  connect(client, &Client::textMessageReceived, this, &ServerController::processTextMessage);
  connect(client, &Client::binaryMessageReceived, this, &ServerController::processBinaryMessage);
  connect(client, &Client::disconnected, this, &ServerController::socketDisconnected);
  clients.append(client);
}
// See abstractcontroller.h for full protocol
void ServerController::processTextMessage(const QString& message) {
  QStringRef request(&message, 0, 2);
  if (request == "GL") { // Get List of stalls

    }
  else if (request == "GS") { // Get Stall data

    }
  else if (request == "IS") { // get Image of Stall

    }
  else if (request == "LG") { // LoGin into stall (stall app)

    }
  else if (request == "LM") { // LoGin into stall (stall app)

    }
  else if (request == "GM") { // Get Menu of stall

    }
  else if (request == "IM") { // get Image of Menu item

    }
  else if (request == "SS") { // Set Stall data (stall app)

    }
  else if (request == "OD") { // OrDer item (kiosk)

    }
  else { // Unknown request

    }
}

void ServerController::processBinaryMessage(const QByteArray& message) {
  int request = message.left(1).toInt();
  if (request == 1) { // Set new stall image

    }
  else if (request == 2) { // Set menu item image

    }
  else { // unknown request

    }
}

QDir ServerController::getAppFolder() {
  QDir data_cursor = QDir::home();
  data_cursor.mkdir(app_name);
  data_cursor.cd(app_name);
  return data_cursor;
}

void ServerController::loadData()
{
  QDir data_cursor = this->getAppFolder();

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

  p_engine->rootContext()->setContextProperty("stallViewModel", QVariant::fromValue(stall_view_model));
}

QJsonObject ServerController::getCompactStallList()
{
  QJsonObject result;
  QJsonArray list;
  for (auto ptr : stall_view_model) {
      Stall& s = *((Stall *) ptr);
      QJsonObject json;
      json["name"] = s.getStallName();
      list.append(json);
    }
  result["stall_list"] = list;
  return result;
}

QJsonObject ServerController::getStallData(int idx)
{
  QJsonObject result;
  Stall& s = *((Stall *) stall_view_model[idx]);
  s.write(result);
  return result;
}

QByteArray ServerController::getStallImage(int idx)
{
  Stall& s = *((Stall *) stall_view_model[idx]);
  QFile img(s.getImagePath().path());
  if (!img.open(QIODevice::ReadOnly))
    throw runtime_error("Could not load stall image from disk.");
  return img.readAll();
}

bool ServerController::loginStall(int idx, const QString &psw)
{
  Stall& s = *((Stall *) stall_view_model[idx]);
  return s.getPassword() == psw;
}

bool ServerController::loginStallasManager(int idx, const QString &psw)
{
  Stall& s = *((Stall *) stall_view_model[idx]);
  return s.getMgmtPassword() == psw;
}

QJsonObject ServerController::getStallMenu(int idx)
{
  QJsonObject result;
  QJsonArray menu;
  Stall& s = *((Stall *) stall_view_model[idx]);
  const QVector<QFood>& menu_vec = *(s.getMenu());
  for (auto f : menu_vec) {
      QJsonObject json;
      f.write(json);
      json["image_path"] = ""; // empty path since image has not been downloaded
      menu.append(json);
    }
  result["menu"] = menu;
  return result;
}

QByteArray ServerController::getMenuItemImage(int sidx, int midx)
{
  Stall& s = *((Stall *) stall_view_model[sidx]);
  QDir stall_path = getAppFolder();
  stall_path.cd(s.getStallName());
  QFile item_img(s.getMenu()->at(midx).getImagePath(stall_path).path());
  return item_img.readAll();
}

bool ServerController::setStallData(int idx, const QJsonObject &data)
{
  try {
    Stall& s = *((Stall *) stall_view_model[idx]);
    s.read(data);
  }  catch (...) {
    return false;
  }
  return true;
}
