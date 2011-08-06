#ifndef DIARY_H
#define DIARY_H

#include "structs.h"
#include "indexer.h"
#include "chatbrowser.h"
#include "tutorial.h"
#include "plotter.h"
#include "utils.h"
#include "fileparsers.h"

#include <QtGui/QMainWindow>
#include <QModelIndex>
#include <QDialog>
#include <qwt_plot_curve.h>
#include <qwt_plot_picker.h>
#include <qwt_symbol.h>
#include <QTimer>


/*
class Indexer;
class SqliteHandler;
class StatExtractor;
class Tutorial;
class ChatBrowser;
*/
namespace Ui
{
    class Diary;
}

class Diary : public QMainWindow
{
    Q_OBJECT

public:
    Diary(QWidget *parent = 0);
    ~Diary();

private:
    Ui::Diary *ui;

    bool displayCalendar;

    int chatIndex;
    int jumpValue;
    int trendsDate;

    SqliteHandler* sqlite;                  // Sqlite handler object
    ChatBrowser* chatBr;                    // Chat browser object
    StatExtractor* statEx;                  // Statistics extractor
    Plotter* plotter;                       // plotting functions
    Tutorial * tute;                        // tutorial object
    QwtPlotCurve* newCurve;                 // Curve used in plot
    QwtPlotCurve* calCurve;                 // Curve for calendar events
    QwtPlotPicker* picker;                  // Plot picker
    Indexer* indexer;                       // Indexer
    QTimer *indexerTimer;                   // timer for index status updation
    FileParsers *parser;                    // File parser to parse calendars, FB-output, tweets
    QList<QString> profiles;                // list of databases available
    QString selectedPath;                   // Path of the database
    QList<ChatSmall> currentChats;          // Snippets of all chats
    ChatFull currentChat;                   // The body of the chat currently being displayed
    QList<Contact> contacts;                // All contacts
    QList<Contact> chatBuddies;             // List of contacts who chat
    QMap<int, QList<Day> > usersDays;       // Time Statistics for each user
    QMap<int, QList<DiaryEvent> > events;   // Day number to diary events map
    QList<Day> timeStats;                   // Time statistics for all users
    QMap<QString, int> contactsMap;         // Contact email to contact id map
    QVector<double> x, y;                   // Valuese for plotting

private slots:
    int findAuto();                 // Autofind database file
    int findFile();                 // find the file

    // Chat/contacts loading
    int loadChats();
    int loadChat(QModelIndex qm);
    int loadChat(int index);
    int loadContacts();
    int showContacts();
    
    // Plotting
    int plotSetup();
    int replot();
    int plot(int replot);
    int plotSenti();
    int plotLength();
    int setWindowSize(int);
    int plotDescribe(QwtDoublePoint point);
    int calendarEvents();
    int toggleCalendar(bool val);

    // Trends Info
    int updateTrends();
    int decrTrendsDate();
    int incrTrendsDate();

    // Paging
    int incrIndex();
    int decrIndex();
    int refresh();

    // Indexing
    int updateIndexingStatus();
    int startIndexing();
    int stopIndexing();

};


#endif // DIARY_H
