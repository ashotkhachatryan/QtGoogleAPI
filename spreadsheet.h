/**
Purpose: Qt Google API

@author Ashot Khachatryan
@version 1.0 03/27/16
*/

#ifndef SPREADSHEET_H
#define SPREADSHEET_H
#include <QStringList>
#include "token.h"

struct Spreadsheet
{
  QString link;
  QString title;
  QString worksheetUrl;
};

#endif
