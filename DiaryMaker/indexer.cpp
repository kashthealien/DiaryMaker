#include "indexer.h"

Indexer::Indexer()
{
    moveToThread(this);
}

void Indexer::run()
{
    stats->extract(contacts, timeStats, contactsMap, usersDays);
    exec();
}
