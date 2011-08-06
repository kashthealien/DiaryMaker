#ifndef STRUCTS_H
#define STRUCTS_H

#include <QDebug>
#include <QVector>
#include <QStringList>
#include <QDateTime>

#define TEN_YEARS 3650

#define TUTE_PATH_1 "/files/tute1.jpeg"
#define TUTE_PATH_2 "/files/tute2.jpeg"
#define TUTE_PATH_3 "/files/tute3.jpeg"
#define TUTE_MESG_1 "Install Google-gears from http://www.gears.google.com for your browser"
#define TUTE_MESG_2 "In Linux you can try installing from commandline"
#define TUTE_MESG_3 "Setup Offline Gmail and enable it"
#define MAX_TUTE_PICS 3
#define NEGATORS_PATH "/files/negators.txt"
#define BOOSTERS_PATH "/files/boosters.txt"
#define EMOTIONS_PATH "/files/emotions.txt"
#define EMOTICON_PATH "/files/emoticon.txt"

struct ChatSmall {
    int id;
    QString time;
    int timeInt;
    QString snippet;
    QString chatee;
};

struct ChatFull {
    int id;
    QString subj;
    QString from;
    QString to;
    QString body;
};

struct Contact {
    // Details
    int id;

    QString name;
    QString email;
    QString number;
    QString facebook;
    QString twitter;

    int chatCount;
    int numLines;
    int numChars;
    int totalTime;
    float happiness;
    float sentiment;
    float value;
    int timeOfDaty;

    QString email2;
    QString number2;
    QString titles;
    QString workPlace;

    Contact() {
        chatCount = 0;
        numLines = 0;
        numChars = 0;
        totalTime = 0;
        timeOfDaty = 0;
        happiness = 0.0;
        sentiment = 0.0;
        value = 0.0;
    }
};



struct DiaryEvent
{
    int id;
    int FriendId;   // If any friend is linked
    QString description;
    DiaryEvent()
    {
        id = 0;
        FriendId = 0;
        description = "";
    }
};

struct Analysis
{
    int numLines;
    int numChars;
    float happiness;
    int totalTime;
    float sentiment;
    int value;

    Analysis() {
        numLines = 0;
        numChars = 0;
        happiness = 0.0;
        totalTime = 0;
        sentiment = 0.0;
        value = 0;
    }
};
struct Day {
    int dayStamp;
    int count;
    int numLines;
    int numChars;
    float happiness;
    float value;
    int totalTime;
    float sentiment;

    Day() {
        dayStamp = 0;
        count = 0;
        numLines = 0;
        numChars = 0;
        happiness = 0.0;
        value = 0.0;
        totalTime = 0;
        sentiment = 0.0;
    }
};

#endif // STRUCTS_H
