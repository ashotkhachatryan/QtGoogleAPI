/**
Purpose: Qt Google API

@author Ashot Khachatryan
@version 1.0 03/27/16
*/

#include "spreadsheet_service.h"
#include "fetcher.h"

QList<Spreadsheet> SpreadsheetService::GetSpreadsheetsList(Token* token)
{
  Fetcher f;
  QPair<QByteArray, QByteArray> pair;
  pair.first = "Authorization";
  pair.second = QByteArray("Bearer ").append(token->GetAccessToken());
  QList<QPair<QByteArray, QByteArray> > header;

  header.append(pair);
  QString spreadSheetList = Info::GoogleSpreadSheetList;

  QList<Spreadsheet> lResult;
  QByteArray bytes = f.get(header, spreadSheetList.append("?alt=json"));
  QScriptValue sc; 
  QScriptEngine engine;
  sc = engine.evaluate("value = " + bytes);
  QScriptValue entries = sc.property("feed").property("entry");
  QScriptValueIterator it(entries);
  while (it.hasNext()) {
    it.next();
    Spreadsheet s;
    s.title = it.value().property("title").property("$t").toString();
    s.link = it.value().property("id").property("$t").toString();
    QScriptValue link = it.value().property("link");
    QScriptValueIterator it1(link);
    it1.next();
    s.worksheetUrl = it1.value().property("href").toString();
    lResult.append(s);
  }
  if (lResult.size() > 0)
    lResult.removeLast();
  return lResult;
}

QList<Worksheet> SpreadsheetService::GetWorksheetsList(Spreadsheet spreadsheet, Token* token)
{
  Fetcher f;

  QPair<QByteArray, QByteArray> pair;
  pair.first = "Authorization";
  pair.second = QByteArray("Bearer ").append(token->GetAccessToken());
  QList<QPair<QByteArray, QByteArray> > header;

  header.append(pair);

  QList<Worksheet> lResult;
  QByteArray bytes = f.get(header, spreadsheet.worksheetUrl.append("?alt=json"));
  QScriptValue sc; 
  QScriptEngine engine;
  sc = engine.evaluate("value = " + bytes);
  QScriptValue entries = sc.property("feed").property("entry");
  QScriptValueIterator it(entries);
  while (it.hasNext()) {
    it.next();
    Worksheet s;
    s.title = it.value().property("title").property("$t").toString();
    QScriptValue link = it.value().property("link");
    QScriptValueIterator it1(link);
    it1.next();
    s.listUrl = it1.value().property("href").toString();
    it1.next();
    s.cellsUrl = it1.value().property("href").toString();
    lResult.append(s);
  }
  if (lResult.size() > 0)
    lResult.removeLast();
  return lResult;
}

QStringList SpreadsheetService::GetCellsList(Worksheet worksheet, Token* token)
{
  Fetcher f;

  QPair<QByteArray, QByteArray> pair;
  pair.first = "Authorization";
  pair.second = QByteArray("Bearer ").append(token->GetAccessToken());
  QList<QPair<QByteArray, QByteArray> > header;

  header.append(pair);

  QStringList lResult;
  QByteArray bytes = f.get(header, worksheet.cellsUrl.append("?alt=json"));
  QScriptValue sc; 
  QScriptEngine engine;
  sc = engine.evaluate("value = " + bytes);
  QScriptValue entries = sc.property("feed").property("entry");
  QScriptValueIterator it(entries);
  while (it.hasNext()) {
    it.next();
    lResult.append(it.value().property("content").property("$t").toString());
  }
  if (lResult.size() > 0)
    lResult.removeLast();
  return lResult;
}
