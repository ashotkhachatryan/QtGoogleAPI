/**
Purpose: Qt Google API

@author Ashot Khachatryan
@version 1.0 03/27/16
*/

#include "token.h"
#include <QDebug>
#include <QDir>
#include "fetcher.h"
#include <QtScript/QScriptEngine>
#include <QtScript/QScriptValueIterator>
#include "info.h"
#include "server.h"
#include <QtGui/QDesktopServices>

#include <iostream>

Token::Token()
  : access_type("offline")
  , response_type("code")
{
  QString path = QDir::homePath() + QDir::separator() + Info::TokenPath;
  QFileInfo file(path);
  if (file.exists() && file.isFile()) {
    QFile f(path);
    if (f.open(QFile::ReadOnly | QFile::Text)) {
      QTextStream in(&f);
      QString fileContent = in.readAll();
      QMap<QString, QString> lResult;
      QScriptValue sc;
      QScriptEngine engine;
      sc = engine.evaluate("value = " + fileContent);
      QScriptValueIterator it(sc);
      while (it.hasNext()) {
        it.next();
        lResult[it.name()] = it.value().toString();
      }
      refresh_token = lResult["refresh_token"];
      access_token = lResult["access_token"];
      token_type = lResult["token_type"];
      expires_in = lResult["expires_in"];
    }
  }
  if (refresh_token.isEmpty()) {
    RevokeToken();
  }
}

QString Token::GetRefreshToken()
{
  return refresh_token;
}

QString Token::GetAccessToken()
{
  return access_token;
}

QString Token::GetTokenType()
{
  return token_type;
}

QString Token::GetExpiresIn()
{
  return expires_in;
}

QString Token::GetAuthorizationUrl(const QString& redirectUri)
{
  QString authorization_url = QString(Info::GoogleOAuth2)
                                      .append("?access_type=").append(access_type)
                                      .append("&response_type=").append(response_type)
                                      .append("&client_id=").append(Info::ClientId)
                                      .append("&scope=");
  std::vector<QString> lScopes;
  lScopes.push_back(Info::GoogleDriveScope);
  lScopes.push_back(Info::GoogleSpreadSheetScope);
  lScopes.push_back(Info::GoogleDocsScope);
  for (int i = 0; i < lScopes.size(); i++) {
    authorization_url.append(lScopes[i]).append(" ");
  }
  authorization_url.append("&redirect_uri=")
                   .append(redirectUri);
  return authorization_url;
}

bool Token::RevokeToken()
{
  int attempt = 0;
  server s;
  int port = GetRandomPort();
  while (!s.start_listen(port)) {
    if (attempt >= 10) {
      return false;
    }
    attempt++;
  }
  QString redirect_uri = QString("http://localhost:").append(QString::number(port)); 
  QString authorization_url = GetAuthorizationUrl(redirect_uri);
  QDesktopServices::openUrl(QUrl(authorization_url));
  QString code = s.waitForCode();
  QByteArray postData;
  postData.append("client_id=" + Info::ClientId + "&");
  postData.append("client_secret=" + Info::ClientSecret + "&");
  postData.append("redirect_uri=" + redirect_uri + "&");
  postData.append("grant_type=authorization_code&");
  postData.append(code);
  QPair<QByteArray, QByteArray> pair("Content-Type", "application/x-www-form-urlencoded");
  QList<QPair<QByteArray, QByteArray> > header;
  header.append(pair);
  Fetcher f;
  QByteArray bytes = f.post(postData, header, QUrl(Info::TokenRequestPath));
  QMap<QString, QString> lPostJson;
  QScriptValue sc; 
  QScriptEngine engine;
  sc = engine.evaluate("value = " + bytes);
  QScriptValueIterator it(sc);
  while (it.hasNext()) {
    it.next();
    lPostJson[it.name()] = it.value().toString();
  }
  access_token = lPostJson["access_token"];
  expires_in = lPostJson["expires_in"];
  token_type = lPostJson["token_type"];
  refresh_token = lPostJson["refresh_token"];
  StoreInJson();
}

void Token::RefreshToken()
{
  QUrl url = QUrl(Info::TokenRequestPath);
  QByteArray postData;
  postData.append("client_id=" + Info::ClientId + "&");
  postData.append("client_secret=" + Info::ClientSecret + "&");
  postData.append("grant_type=refresh_token&");
  postData.append("refresh_token=" + refresh_token);
  QPair<QByteArray, QByteArray> pair("Content-Type", "application/x-www-form-urlencoded");
  QList<QPair<QByteArray, QByteArray> > header;
  header.append(pair);
  Fetcher f;
  QByteArray bytes = f.post(postData, header, url);
  QMap<QString, QString> lPostJson;
  QScriptValue sc; 
  QScriptEngine engine;
  sc = engine.evaluate("value = " + bytes);
  QScriptValueIterator it(sc);
  while (it.hasNext()) {
    it.next();
    lPostJson[it.name()] = it.value().toString();
  }
  access_token = lPostJson["access_token"];
  expires_in = lPostJson["expires_in"];
  token_type = lPostJson["token_type"];
  StoreInJson();
}

void Token::StoreInJson()
{
  QString lResult = QString("{\n")
                    .append("\"refresh_token\": ").append("\"").append(refresh_token + "\",\n")
                    .append("\"access_token\": ").append("\"").append(access_token + "\",\n")
                    .append("\"token_type\": ").append("\"").append(token_type + "\",\n")
                    .append("\"expires_in\": ").append("\"").append(expires_in + "\"\n")
                    .append("}");
  QString fileName = QDir::homePath() + QDir::separator() + Info::TokenPath;
  QFileInfo fileInfo(fileName);
  if (!fileInfo.dir().exists()) {
    QDir().mkdir(fileInfo.dir().absolutePath());
  }
  QFile file(fileName);
  if (file.open(QIODevice::ReadWrite)) {
    QTextStream stream(&file);
    stream << lResult;
  }
}

// Get random port in the range [2000, 10000)
int Token::GetRandomPort()
{
  QTime now = QTime::currentTime();
  qsrand(now.msec());
  return (qrand() % 8000) + 2000;
}
