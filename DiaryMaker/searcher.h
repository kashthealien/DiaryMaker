#ifndef SEARCHER_H
#define SEARCHER_H

#include <QObject>

class Searcher : public QObject
{
public:
    Searcher();
public slots:
    int searchClicked();            // Search text clicked
    int searchChanged();            // Search term change
    int searchDone();               // Search done
};

#endif // SEARCHER_H
