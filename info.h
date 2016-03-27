/**
Purpose: Qt Google API

@author Ashot Khachatryan
@version 1.0 03/27/16
*/

#ifndef INFO_H
#define INFO_H
#include <QString>

struct Info {
  static const QString ClientId;
  static const QString ClientSecret;

  static const QString GoogleDriveScope;
  static const QString GoogleSpreadSheetScope;
  static const QString GoogleSpreadSheetList;
  static const QString GoogleDocsScope;
  static const QString GoogleOAuth2;

  static const QString TokenRequestPath;
  static const QString TokenPath;
};

#endif
