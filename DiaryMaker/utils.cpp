#include "utils.h"

Utils::Utils()
{
}

int Utils::getTimeStamp(int relDay)
{
    // January 1st 2005 = 1104555600
    // Subtract that value from the time stamp
    int relTime = relDay*86400;
    int time = relTime + START;
    return time;
}
int Utils::getDayNumber(int timeStamp)
{
    // January 1st 2005 = 1104537600
    // Subtract that value from the time stamp
    QDateTime time; time.setTime_t(timeStamp);    
    int relTime = timeStamp - START;
    int relDay = relTime/86400;
    return relDay;
}
QString Utils::timeStr(int timeStamp)
{
    QDateTime time; time.setTime_t(timeStamp);
    return time.toString("ddd MMMM d yyyy");
}

int Utils::timeInt(QString day)
{
    int date, month, year;
    QStringList list = day.split('/');
    QString dateStr = list[0];
    QString montStr = list[1];
    QString yearStr = list[2];
    date = dateStr.toInt();
    month = montStr.toInt();
    year = yearStr.toInt();
    QDate myDate(year, month, date);
    QTime myTime(0,0,0,0);
    QDateTime time(myDate, myTime, Qt::UTC);
    int dayNumber = Utils::getDayNumber(time.toTime_t());
    return dayNumber;
}

int Utils::getTime(int timeStamp)
{
    QDateTime time;//(timeStamp);
    time.setTime_t(timeStamp);
    int out = time.time().hour()*100 + time.time().minute();
    return out;
}
QString Utils::getLocation()
{
    OS os = getOS();
    BROWSER browser = getBrowser();
    QString location = "";
    /*
    Windows Vista
    * Internet Explorer: C:\Users\<user>\AppData\LocalLow\Google\Google Gears for Internet Explorer
    * Firefox: Database files are stored in the user profile directory. C:\Users\<user>\AppData\Local\Mozilla\Firefox\Profiles\{PROFILE}.default\Google Gears for Firefox
    * Google Chrome: Database files are stored in the user profile directory. C:\Users\<user>\AppData\Local\Google\Chrome\User Data\Default\Plugin Data\Google Gears

    Windows XP
    * Internet Explorer: C:\Documents and Settings\<user>\Local Settings\Application Data\Google\Google Gears for Internet Explorer
    * Firefox: Database files are stored in the user profile directory. C:\Documents and Settings\<user>\Local Settings\Application Data\Mozilla\Firefox\Profiles\{PROFILE}.default\Google Gears for Firefox
    * Google Chrome: Database files are stored in the user profile directory. C:\Documents and Settings\<user>\Local Settings\Application Data\Google\Chrome\User Data\Default\Plugin Data\Google Gears

    Mac OS X
    * Firefox: Database files are stored in the user profile directory. Users/<user>/Library/Caches/Firefox/Profiles/{PROFILE}.default/Google Gears for Firefox
    * Safari: ~/Library/Application Support/Google/Google Gears for Safari

    Linux Firefox: Database files are stored in the user home directory. <user>/.mozilla/firefox/{PROFILE}.default/Google Gears for Firefox

    Microsoft Windows Mobile Internet Explorer: Database files are stored in the Application Data directory. \Application Data\Google\Google Gears for Internet Explorer
     */
    if (os == VISTA) {
        if (browser == FF) {
        } else if (browser == CHROME) {
        } else if (browser == IE) {
        } else {
        }
    } else if (os == XP) {
        if (browser == FF) {
        } else if (browser == CHROME) {
        } else if (browser == IE) {
        } else {
        }
    } else if (os == MAC) {
        if (browser == FF) {
        } else if (browser == SAFARI) {
        } else {
        }
    }

    return "~/.mozilla/firefox/";
}

QString Utils::STR(int x)
{
    QString a; a.setNum(x);
    return a;
}

QString Utils::scoreText(int value)
{
    QString out,num;
    if (value > 1000000) {
        out = Utils::STR(value/1000000)+ " Million";
    } else if (value > 1000) {
        out = Utils::STR(value/1000) + " Thousand";
    } else {
        out = Utils::STR(value);;
    }
    return out;
}

OS Utils::getOS()
{
    return LINUX;
}

BROWSER Utils::getBrowser()
{
    return FF;
}
