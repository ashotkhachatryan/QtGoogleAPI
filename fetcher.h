/**
Purpose: Qt Google API

@author Ashot Khachatryan
@version 1.0 03/27/16
*/

#ifndef FETCHER_H
#define FETCHER_H

#include <QtCore>
#include <QtNetwork/QtNetwork>
#include <QDebug>
#include <QtScript/QScriptEngine>
#include <QtScript/QScriptValueIterator>

class Fetcher: public QObject
{
  Q_OBJECT
  public:
    Fetcher(QObject *p = 0);
    QByteArray get(const QList<QPair<QByteArray, QByteArray> >& header, const QUrl &url);
    QByteArray post(const QByteArray& postData, const QList<QPair<QByteArray, QByteArray> >& header, const QUrl &url);
  private:
    QNetworkAccessManager nam;
    QNetworkReply *reply;
};

#endif
