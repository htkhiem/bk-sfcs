#include "servercontroller.h"
#include "../../backend/BK-SFCS-Backend/src/menu.h"

ServerController::ServerController(QQmlApplicationEngine *eng, QObject *parent) :
  QObject(parent),
  web_socket_server(new QWebSocketServer(QStringLiteral("BK-SFCS Server"), QWebSocketServer::NonSecureMode, this)),
  app_name(web_socket_server->serverName()),
  p_engine(eng)
{
  // Loads disk data into RAM
  loadData();
  // Loads server URL from config file
  QDir data_cursor = this->getAppFolder();
  QFile server_conf(data_cursor.filePath("server.conf"));
  bool result;
  if (server_conf.exists()) {
      if (!server_conf.open(QIODevice::ReadOnly)) {
          throw runtime_error("Cannot read configuration file.");
        }
      QString server_address = QString(server_conf.readLine());
      server_address.remove(server_address.length() - 1, 1);
      qDebug() << server_address;

      int server_port = QString(server_conf.readLine()).toInt();
      qDebug() << server_port;

      result = web_socket_server->listen(QHostAddress(server_address),
                                         server_port);
      server_conf.close();
    }
  else {
      qDebug() << "Creating new configuration file...";
      if (!server_conf.open(QIODevice::WriteOnly)) {
          throw runtime_error("Cannot write initial configuration file.");
        }
      server_conf.write(QByteArray("::1\n25678")); // defaults to localhost
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
  client->setClientIdx(clients.size());
  qDebug() << "New client connected with index " << clients.size();
  clients.append(client);

}
// See abstractcontroller.h for full protocol
void ServerController::processTextMessage(const QString& message) {
  qDebug() << "Text message received: " << message;
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
        response += QString("%1").arg(1, 2, 10, QChar('0')).toUtf8();
        int idx = request[1].toInt();
        qDebug() << "Image of stall " << idx << " requested.";
        QByteArray name = ((Stall *) stall_view_model[idx])->getImagePath()
            .fileName().toUtf8();
        QByteArray image = getStallImage(idx);
        response += QString("%1").arg(message.toUtf8().size(), 2, 10, QChar('0')).toUtf8();
        response += QString("%1").arg(name.size(), 2, 10, QChar('0')).toUtf8();
        response += message.toUtf8() + name + image;
        qDebug() << "Replying with " << response.left(48) << " (...)";
        client->sendBinaryMessage(response);
      }  catch (...) {
        response.clear();
        response += QString("%1").arg(0, 2, 10, QChar('0')).toUtf8();
        response += message.toUtf8().size();
        response += message.toUtf8();
      }
    }
  else if (request[0] == "LG") { // LoGin into stall (stall app)
      QString response;
      if (loginStall(request[1].toInt(), request[2])) {
          client->setType(stall);
          client->setClientIdx(request[1].toInt());
          response = "OK " + message;
        }
      else {
          response = "NO " + message;
        }
      client->sendTextMessage(response);
    }
  else if (request[0] == "LM") { // Login with Management rights (stall app)
      QString response;
      if (client->getType() == stall &&
          loginStallasManager(client->getClientIdx(), request[2])) {
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
        response += QString("%1").arg(1, 2, 10, QChar('0')).toUtf8();
        int sidx = request[1].toInt();
        int midx = request[2].toInt();
        QDir stall_path = getAppFolder();
        stall_path.cd(((Stall *) stall_view_model[sidx])->getStallName());
        QByteArray name =
            ((Stall *) stall_view_model[sidx])->getMenu()->at(midx)
            .getImagePath(stall_path.path()).fileName().toUtf8();
        QByteArray image = getMenuItemImage(sidx, midx);
        response += QString("%1").arg(message.toUtf8().size(), 2, 10, QChar('0')).toUtf8();
        response += QString("%1").arg(name.size(), 2, 10, QChar('0')).toUtf8();
        response += message.toUtf8() + name + image;
        qDebug() << "Replying with " << response.left(48) << " (...)";
        client->sendBinaryMessage(response);
      }  catch (...) {
        response.clear();
        response += QString("%1").arg(0, 2, 10, QChar('0')).toUtf8();
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
      for (auto p : clients) {
          if (p->getType() == ClientType::stall) {
              if (p->getClientIdx() == request[2].toInt()) {
                  // Forward order request to stall
                  p->sendTextMessage(message);
                  break;
                }
            }
        }
    }
  else if (request[0] == "OK" || request[0] == "NO") { // from Stall client (order replies)
      // Third element should be kiosk index
      int kiosk_idx = request[2].toInt();
      clients[kiosk_idx]->sendTextMessage(message);
    }
  else if (request[0] == "KX") {
      client->sendTextMessage("OK KX " + QString(client->getClientIdx()));
    }
  else { // Unknown request
      client->sendTextMessage("NO WTF");
    }
}

void ServerController::processBinaryMessage(const QByteArray& message) {
  Client *client = qobject_cast<Client *>(sender());
  int request = message.left(1).toInt();
  if (request == 1) { // Set new stall image
      int idx = message.mid(1, 4).toInt();
      int sz = message.mid(5, 4).toInt();
      QString filename = message.mid(9, sz);
      QDir data_cursor = this->getAppFolder();
      data_cursor.mkdir(((Stall *) stall_view_model[idx])->getStallName());
      data_cursor.cd(((Stall *) stall_view_model[idx])->getStallName());
      QFile stall_image(data_cursor.filePath(filename));
      if (!stall_image.open(QIODevice::WriteOnly)) {
          throw runtime_error("Unable to write uploaded stall image to disk");
        }
      stall_image.write(message.right(message.size() - 9 - sz));
      stall_image.close();
      ((Stall *) stall_view_model[idx])->setImagePath(filename);
    }
  else if (request == 2) { // Set menu item image
      int stall_idx = message.mid(1, 4).toInt();
      int item_idx = message.mid(5, 4).toInt();
      int sz = message.mid(9, 4).toInt();
      QString filename = message.mid(13, sz);
      QDir data_cursor = this->getAppFolder();
      data_cursor.mkdir(((Stall *) stall_view_model[stall_idx])->getStallName());
      data_cursor.cd(((Stall *) stall_view_model[stall_idx])->getStallName());
      QFile stall_image(data_cursor.filePath(filename));
      if (!stall_image.open(QIODevice::WriteOnly)) {
          throw runtime_error("Unable to write uploaded stall image to disk");
        }
      stall_image.write(message.right(message.size() - 13 - sz));
      stall_image.close();
      (*((Stall *) stall_view_model[stall_idx])->getEditableMenu())[item_idx].setImageName(filename);
    }
  else { // unknown request
      client->sendTextMessage("NO WTF");
    }
}

void ServerController::socketDisconnected() {

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
  QFile item_img(s.getMenu()->at(midx).getImagePath(stall_path.path()).path());
  if (!item_img.open(QIODevice::ReadOnly))
    throw runtime_error("Could not load stall image from disk.");
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