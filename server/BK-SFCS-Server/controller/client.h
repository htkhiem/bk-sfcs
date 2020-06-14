#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include "../../backend/BK-SFCS-Backend/src/common.h"
enum ClientType {kiosk, stall};

class Client : public QObject
{
  Q_OBJECT
  ClientType type;
  int idx; // if type != stall, this field is the same as index within list of clients.
  QWebSocket* socket;
  int currently_viewing_stall; // for kiosk only (so server knows which stall to notify about menu changes)
public:
  explicit Client(QWebSocket *sk, QObject *parent = nullptr);
  ClientType getType() const;
  void setType(const ClientType &value);

  QWebSocket *getSocket() const;
  void setSocket(QWebSocket *value);
  void sendTextMessage(const QString& message);
  void sendBinaryMessage(const QByteArray& message);
  int getClientIdx() const;
  void setClientIdx(int value);

  int getCurrentlyViewingStall() const;
  void setCurrentlyViewingStall(int value);

signals:
  void textMessageReceived(const QString& message);
  void binaryMessageReceived(const QByteArray& message);
  void disconnected();
};

#endif // CLIENT_H
