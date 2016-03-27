/**
Purpose: Qt Google API

@author Ashot Khachatryan
@version 1.0 03/27/16
*/

#ifndef SPREADSHEET_SERVICE_H
#define SPREADSHEET_SERVICE_H

#include <QStringList>
#include "token.h"
#include "spreadsheet.h"
#include "worksheet.h"

class SpreadsheetService : QObject
{
  Q_OBJECT
public:
  QList<Spreadsheet> GetSpreadsheetsList(Token* token);
  QList<Worksheet> GetWorksheetsList(Spreadsheet spreadsheet, Token* token);
  QStringList GetCellsList(Worksheet, Token* token);
};

#endif
