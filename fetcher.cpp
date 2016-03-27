/**
Purpose: Qt Google API

@author Ashot Khachatryan
@version 1.0 03/27/16
*/

#include <QtCore>
#include <QtNetwork/QtNetwork>
#include <QDebug>
#include "fetcher.h"
#include <iostream>

void sleep( int millisecondsToWait )
{
  QTime dieTime = QTime::currentTime().addMSecs( millisecondsToWait );
  while( QTime::currentTime() < dieTime )
  {
    QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );
  }
}

Fetcher::Fetcher(QObject *p): 
      QObject(p), 
      reply(0) 
{
}

QByteArray Fetcher::get(const QList<QPair<QByteArray, QByteArray> >& header, const QUrl &url) {
  QNetworkRequest req(url);
  for (int i = 0; i < header.size(); i++) {
    req.setRawHeader(header[i].first, header[i].second);
  }
  reply = nam.get(req);
  while(reply->bytesAvailable() == 0) {
    sleep(1000);
  }
  return reply->readAll();
}

QByteArray Fetcher::post(const QByteArray& postData, const QList<QPair<QByteArray, QByteArray> >& header, const QUrl &url) {
  QNetworkRequest req(url);
  for (int i = 0; i < header.size(); i++) {
    req.setRawHeader(header[i].first, header[i].second);
  }
  reply = nam.post(req, postData);

  while(reply->bytesAvailable() == 0) {
    sleep(1000);
  }
  return reply->readAll();
}
