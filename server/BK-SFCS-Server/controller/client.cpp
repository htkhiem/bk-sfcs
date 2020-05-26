#include "client.h"

ClientType Client::getType() const
{
  return type;
}

void Client::setType(const ClientType &value)
{
  type = value;
}

QWebSocket *Client::getSocket() const
{
  return socket;
}

void Client::setSocket(QWebSocket *value)
{
  socket = value;
}

Client::Client(QWebSocket *sk, QObject *parent) :
  QObject(parent), type(kiosk), stall_idx(-1), socket(sk)
{
  connect(sk, &QWebSocket::textMessageReceived, this, &Client::textMessageReceived);
  connect(sk, &QWebSocket::binaryMessageReceived, this, &Client::binaryMessageReceived);
  connect(sk, &QWebSocket::disconnected, this, &Client::disconnected);
}
