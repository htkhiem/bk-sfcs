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

void Client::sendTextMessage(const QString &message)
{
  socket->sendTextMessage(message);
}

void Client::sendBinaryMessage(const QByteArray &message)
{
  socket->sendBinaryMessage(message);
}

int Client::getClientIdx() const
{
  return idx;
}

void Client::setClientIdx(int value)
{
  idx = value;
}

int Client::getCurrentlyViewingStall() const
{
    return currently_viewing_stall;
}

void Client::setCurrentlyViewingStall(int value)
{
    currently_viewing_stall = value;
}

void Client::close()
{
    socket->close(QWebSocketProtocol::CloseCodeNormal, "Server closed connection");
}

QString Client::getId()
{
    QString result;
    result += socket->peerAddress().toString();
    if (getType() == ClientType::stall) result += "(stall ID " + QString::number(getClientIdx()) + ")";
    return result;
}

bool Client::isStall()
{
    return (getType() == ClientType::stall);
}

Client::Client(QWebSocket *sk, QObject *parent) :
    QObject(parent), type(kiosk), idx(-1), socket(sk), currently_viewing_stall(-1)
{
    connect(sk, &QWebSocket::textMessageReceived, this, &Client::textMessageReceived);
  connect(sk, &QWebSocket::binaryMessageReceived, this, &Client::binaryMessageReceived);
  connect(sk, &QWebSocket::disconnected, this, &Client::disconnected);
}
