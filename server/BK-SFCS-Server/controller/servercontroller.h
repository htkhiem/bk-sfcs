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

  QQmlApplicationEngine* p_engine;

  /** Loads stall data (and their menus) from ~/sfcs_data. Also populates the
   * stall view model. */
  void loadData();

  /** Saves stall data to disk after running. This includes their menus. */
  void saveData();

  QJsonObject getCompactStallList();
  QJsonObject getStallData(int idx);
  QByteArray getStallImage(int idx);
  bool loginStall(int idx, const QString& psw);
  bool loginStallasManager(int idx, const QString& psw);
  QJsonObject getStallMenu(int idx);
  QByteArray getMenuItemImage(int sidx, int midx);
  QByteArray getFullResMenuItemImage(int sidx, int midx);
  bool setStallData(int idx, const QJsonObject& data);
  void resizeToThumbnail(QImage& source);
public:
  QList<QObject *> clients;
  QList<QObject *> menu_view_model;
  QList<QObject *> stall_view_model;

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
