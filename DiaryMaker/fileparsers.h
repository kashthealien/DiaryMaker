#ifndef FILEPARSERS_H
#define FILEPARSERS_H

#include "structs.h"
#include <QObject>

class FileParsers : public QObject
{
    Q_OBJECT
public:
    FileParsers() : QObject(){}
    int parseFbDiary(QString fileName);
    int parseTwitterDiary(QString fileName);
    int parseFbFriends(QString fileName);
    int parseCustomDiary(QString fileName);
    QList<DiaryEvent> getEvents(int day)
    {return events[day];}

private:
    QMap<int, QList<DiaryEvent> > events;
public slots:
    int facebookDiary();            // Upload facebook diary
    int facebookFriends();          // Upload facebook friends details
    int tweetDiary();               // Upload tweets
    int customDiary();              // Upload custom diary

};

#endif // FILEPARSERS_H
