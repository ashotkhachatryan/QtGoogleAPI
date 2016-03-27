/**
Purpose: Qt Google API

@author Ashot Khachatryan
@version 1.0 03/27/16
*/

#include <QtGui/QApplication>
#include <QByteArray>
#include <QObject>

#include <iostream>
#include <memory>
#include "fetcher.h"
#include "token.h"
#include "spreadsheet_service.h"

int main(int argc, char* argv[])
{
  QApplication a(argc, argv);

  std::auto_ptr<Token> t;
  t.reset(new Token());
  t->RefreshToken();

  std::auto_ptr<SpreadsheetService> s;
  s.reset(new SpreadsheetService());

  // Getting spreadsheets list
  QList<Spreadsheet> spreadsheets = s->GetSpreadsheetsList(t.get());

  // Getting worksheets list in first spreadsheet
  QList<Worksheet> worksheets = s->GetWorksheetsList(spreadsheets[0], t.get());

  // Getting cells list in second worksheet
  QStringList c = s->GetCellsList(worksheets[2], t.get());
  for (int i = 0; i < c.size(); i++)
  {
      qDebug() << c[i];
  }

  return a.exec();
}
