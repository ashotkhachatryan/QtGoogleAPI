/**
Purpose: Qt Google API

@author Ashot Khachatryan
@version 1.0 03/27/16
*/

#ifndef SERVER_H
#define SERVER_H

#include <QtNetwork/QtNetwork>

class server : public QTcpServer
{
  Q_OBJECT
  public:
    explicit server(QObject *parent = 0);
    ~server();
    QTcpSocket server_socket;
  public slots:
    bool start_listen(int port);
    QString waitForCode();
  protected:
    void incomingConnection( int descriptor );
};
#endif
