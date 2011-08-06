#ifndef STATSEXTRAXTOR_H
#define STATSEXTRAXTOR_H
#include "sentimentanalyser.h"
#include "sqlitehandler.h"

class StatExtractor
{
private:
    SqliteHandler *handler;
    SentimentAnalyser *analyser;
public:
    StatExtractor();
    void setHandler(SqliteHandler *handle) {handler = handle;}
    int extract(QList<Contact> &contacts, QList<Day> &timeStats, QMap <QString, int> &contactsMap, QMap<int, QList<Day> >& userDayMatrix);
    QString getStatus();
    int analyseChat(QString &full, Analysis &analysis);
    bool isActive() {return (!done);}
private:
    int purify(QString& full, QString& good);
    int initDayList(QList<Day>& dayList);
    int totalMessages;
    int completedMessages;
    bool done;
};

#endif // STATSEXTRAXTOR_H
