/**
Purpose: Qt Google API

@author Ashot Khachatryan
@version 1.0 03/27/16
*/

#ifndef TOKEN_H
#define TOKEN_H

#include <QString>
#include "info.h"

class Token
{
public:
  Token();
  QString GetRefreshToken();
  QString GetAccessToken();
  QString GetTokenType();
  QString GetExpiresIn();
  bool RevokeToken();
  void RefreshToken();
private:
  void StoreInJson();
  int GetRandomPort();
  QString GetAuthorizationUrl(const QString& redirectUri);
private:
  QString refresh_token;
  QString access_token;
  QString token_type;
  QString expires_in;

  QString access_type;
  QString response_type;
};

#endif
