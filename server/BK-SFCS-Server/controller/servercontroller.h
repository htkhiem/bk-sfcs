#ifndef SERVERCONTROLLER_H
#define SERVERCONTROLLER_H

#include <QObject>
#include "../../backend/BK-SFCS-Backend/src/common.h"
#include "client.h"
class ServerController : public QObject
{
  Q_OBJECT
  QWebSocketServer *web_socket_server;
  QHostAddress address;
  QString app_name;
  QDir getAppFolder();
  QList<Client *> clients;
protected:
  QQmlApplicationEngine* p_eng;
public:
  explicit ServerController(QQmlApplicationEngine *eng, QObject *parent = nullptr);
  ~ServerController();
public slots:
  void onNewConnection();
  void processTextMessage(const QString& message);
  void processBinaryMessage(const QByteArray& message);
  void socketDisconnected();
signals:
  void closed();
};

#endif // SERVERCONTROLLER_H
