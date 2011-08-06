#ifndef UTILS_H
#define UTILS_H
#include "structs.h"
#include <QDebug>
#include <QVector>
#include <QStringList>
#include <QDateTime>
#define START 1104537600
enum OS {OTHER_OS = 0, VISTA, XP, MAC, LINUX};
enum BROWSER {OTHER_BR = 0, FF, CHROME, IE, SAFARI};

class Utils
{
public:
    Utils();
    static int getTime(int timeStamp);
    static int getTimeStamp(int relDay);
    static int timeInt(QString day);
    static int getDayNumber(int timeStamp);
    static QString timeStr(int timeStamp);
    static QString STR(int x);
    static QString scoreText(int value);
    static OS getOS();
    static BROWSER getBrowser();
    static QString getLocation();
};

#endif // UTILS_H
