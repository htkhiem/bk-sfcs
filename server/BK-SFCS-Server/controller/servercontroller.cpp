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
  Client *client = qobject_cast<Client *>(sender());
  QStringList request = message.split(' ', QString::SkipEmptyParts);
  if (request[0] == "GL") { // Get List of stalls
      QString response = "OK " + message + " "
          + QJsonDocument(getCompactStallList()).toJson();
      client->sendTextMessage(response);
    }
  else if (request[0] == "GS") { // Get Stall data
      QString response;
      try {
        response = "OK " + message + " "
            + QJsonDocument(getStallData(request[1].toInt())).toJson();
      }  catch (...) {
        response = "NO " + message;
      }
      client->sendTextMessage(response);
    }
  else if (request[0] == "IS") { // get Image of Stall
      QByteArray response;
      try {
        response.append('1');
        int idx = request[1].toInt();
        QByteArray name = ((Stall *) stall_view_model[idx])->getImagePath()
            .fileName().toUtf8();
        QByteArray image = getStallImage(idx);

        response += message.toUtf8().size();
        response += name.size();
        response += message.toUtf8() + name + image;
        client->sendBinaryMessage(response);
      }  catch (...) {
        response.append('0');
        response += message.toUtf8().size();
        response += message.toUtf8();
      }
    }
  else if (request[0] == "LG") { // LoGin into stall (stall app)
      QString response;
      if (loginStall(request[1].toInt(), request[2])) {
          client->setType(stall);
          client->setStallIdx(request[1].toInt());
          response = "OK " + message;
        }
      else {
          response = "NO " + message;
        }
      client->sendTextMessage(response);
    }
  else if (request[0] == "LM") { // LoGin with management rights (stall app)
      QString response;
      if (client->getType() == stall &&
          loginStallasManager(client->getStallIdx(), request[2])) {
          response = "OK " + message;
        }
      else {
          response = "NO " + message;
        }
      client->sendTextMessage(response);
    }
  else if (request[0] == "GM") { // Get Menu of stall
      QString response;
      try {
        response = "OK " + message + " "
            + QJsonDocument(getStallMenu(request[1].toInt())).toJson();
      }  catch (...) {
        response = "NO " + message;
      }
      client->sendTextMessage(response);
    }
  else if (request[0] == "IM") { // get Image of Menu item
      QByteArray response;
      try {
        response.append('1');
        int sidx = request[1].toInt();
        int midx = request[2].toInt();
        QDir stall_path = getAppFolder();
        stall_path.cd(((Stall *) stall_view_model[sidx])->getStallName());
        QByteArray name =
            ((Stall *) stall_view_model[sidx])->getMenu()->at(midx)
            .getImagePath(stall_path).fileName().toUtf8();
        QByteArray image = getMenuItemImage(sidx, midx);

        response += message.toUtf8().size();
        response += name.size();
        response += message.toUtf8() + name + image;
        client->sendBinaryMessage(response);
      }  catch (...) {
        response.append('0');
        response += message.toUtf8().size();
        response += message.toUtf8();
      }
    }
  else if (request[0] == "SS") { // Set Stall data (stall app)
      QString response;
      try {
        int idx = request[1].toInt();
        QJsonObject data = QJsonDocument(QJsonDocument::fromJson(
                                           request[2].toUtf8())).object();
        setStallData(idx, data);
        response = "OK " + request[0] + " " + request[1]; // do not send the JSON part back
      }  catch (...) {
        response = "NO " + request[0] + " " + request[1];
      }
      client->sendTextMessage(response);
    }
  else if (request[0] == "OD") { // OrDer item (kiosk)
      // TODO
    }
  else { // Unknown request
      client->sendTextMessage("NO WTF");
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
