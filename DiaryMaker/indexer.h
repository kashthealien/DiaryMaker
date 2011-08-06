#ifndef INDEXER_H
#define INDEXER_H

#include <QThread>
#include "statextractor.h"

class Indexer : public QThread
{
public:
    Indexer();
    void run();

    // Inline functions
    int setContacts(QList<Contact> &conts, QMap<QString, int> &map)
    { contactsMap = map; contacts = conts; return 0;}
    int setStats(QList<Day> &tStats, QMap<int, QList<Day> > &users)
    { timeStats = tStats; this->usersDays = users; return 0;}
    int setStatExtractor(StatExtractor* statEx)
    {stats = statEx; return 0;}
    int getTimeStats(QList<Day> &tStats, QMap<int, QList<Day> > &users)
    { tStats = timeStats; users = usersDays; return 0;}
    int getContacts(QList<Contact> &conts, QMap<QString, int> &map)
    { conts = contacts; map = contactsMap; return 0;}
private:
    StatExtractor* stats;
    QList<Contact> contacts;
    QMap<int, QList<Day> > usersDays;
    QList<Day> timeStats;
    QMap<QString, int> contactsMap;
};

#endif // INDEXER_H
