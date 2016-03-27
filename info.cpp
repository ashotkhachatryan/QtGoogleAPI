/**
Purpose: Qt Google API

@author Ashot Khachatryan
@version 1.0 03/27/16
*/

#include "info.h"

const QString Info::ClientId = "Your Client Id";
const QString Info::ClientSecret = "Your Secret";

const QString Info::GoogleDriveScope = "https://www.googleapis.com/auth/drive";
const QString Info::GoogleSpreadSheetScope = "https://spreadsheets.google.com/feeds";
const QString Info::GoogleSpreadSheetList = "https://spreadsheets.google.com/feeds/spreadsheets/private/full";
const QString Info::GoogleDocsScope = "https://docs.google.com/feeds";
const QString Info::GoogleOAuth2 = "https://accounts.google.com/o/oauth2/auth";

const QString Info::TokenRequestPath = "https://www.googleapis.com/oauth2/v4/token";
const QString Info::TokenPath = ".gdrive/token_info.json";
