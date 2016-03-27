/**
Purpose: Qt Google API

@author Ashot Khachatryan
@version 1.0 03/27/16
*/

#include "server.h"
#include <iostream>

server::server(QObject *parent) :
  QTcpServer(parent)
{
  server_socket.setSocketOption(QAbstractSocket::KeepAliveOption, true );
}

bool server::start_listen(int port)
{
  if(!this->listen(QHostAddress::LocalHost, port))
    return false;
    return true;
}

void server::incomingConnection(int descriptor)
{
  if(!server_socket.setSocketDescriptor(descriptor))
  {
    qDebug() << "Socket error!";
    return;
  }
}

void delay( int millisecondsToWait )
{
  QTime dieTime = QTime::currentTime().addMSecs( millisecondsToWait );
  while( QTime::currentTime() < dieTime )
  {
    QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );
  }
}

QString server::waitForCode()
{
  while(server_socket.bytesAvailable() == 0) {
    delay(1000);
  }
  QByteArray array = server_socket.readLine( server_socket.bytesAvailable() );
  server_socket.write("Received");
  return QString(array.split(' ')[1].remove(0, 2));
}

server::~server()
{
  server_socket.disconnectFromHost();
  server_socket.waitForDisconnected();
}
