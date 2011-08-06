#include "sqlitehandler.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QDateTime>
#include <QVariant>

#include <QFile>
#include <QObject>
#include <qdir.h>

SqliteHandler::SqliteHandler()
{
}

bool SqliteHandler::openDB()
{
     // Find QSLite driver
     QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");

     // NOTE: We have to store database file into user home folder in Linux
     QString path(QDir::home().path());
     path.append(QDir::separator()).append("my.db.sqlite");
     path = QDir::toNativeSeparators(path);
     db.setDatabaseName(path);

     this->setPath(path);
     
     QMessageBox::critical(0,"Done","Created the database ",QMessageBox::Ok);
     return true;
}


bool SqliteHandler::createConnection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName("localhost");
    db.setDatabaseName(path);
    if (!db.open()) {
        QMessageBox::critical(0,"Error","No database or incorrect path "+path,QMessageBox::Ok);
        return false;
    } else {
        QMessageBox::critical(0,"Done","Using the database ",QMessageBox::Ok);
        return true;
    }
}

int SqliteHandler::createTable(void)
{
     QSqlQuery query;
     QString str = "create table WORDINDEX (word char(30), chatNum integer)";
     
     if(!query.exec(str))
	  QMessageBox::critical(0,"Error","create table failed",QMessageBox::Ok);
     else
	  QMessageBox::critical(0,"Done","WORDINDEX table created",QMessageBox::Ok);
     query.next();
     
     return 0;
}

int SqliteHandler::insertWord(QString str)
{
     QSqlQuery query;
     //query.exec(str);
     if(!query.exec(str))
	  QMessageBox::critical(0,"Error","Query " +str+" failed",QMessageBox::Ok);
     /*else
       QMessageBox::critical(0,"Done","Query " +str+" Ok",QMessageBox::Ok);*/
     query.next();
     
     return 0;
}

int SqliteHandler::getFiles(QString str, QSet<int> &files)
{
     QSqlQuery query;

     if(!query.exec(str))
	  QMessageBox::critical(0,"Error","Query " +str+" failed",QMessageBox::Ok);
     
     while(query.next()){
	  int filename;
	  filename = query.value(0).toInt();
	  
	  files.insert(filename);
     }
     
     return 0;
}


// int SqliteHandler::getChats(QString str, QList<ChatSmall>& chats)
// {
//     QSqlQuery query;
//     query.exec(str);

//     while(query.next()) {
//         ChatSmall chat;
//         unsigned long long int time = query.value(5).toULongLong();
//         time /= 1000;
//         QDateTime timestamp;
//         timestamp.setTime_t(time);
//         chat.timeInt = time;
//         chat.id = query.value(0).toInt();
//         chat.time = timestamp.toString();
//         chat.snippet = query.value(22).toString();
//         chats.push_back(chat);
//     }

//     return 0;
// }

// int SqliteHandler::getChat(QString str, ChatFull &chat)
// {
//     QSqlQuery query;
//     query.exec(str);
//     query.next();
//     chat.subj = query.value(0).toString();
//     chat.from = query.value(2).toString() + " || " + query.value(3).toString() + " || " + query.value(4).toString();
//     chat.to = query.value(5).toString() + " || " + query.value(6).toString() + " || " + query.value(7).toString();
//     chat.body = query.value(1).toString();
//     return 0;
// }

// int SqliteHandler::getContacts1(QString str, QList<Contact>& contacts)
// {
//     QSqlQuery query;
//     query.exec(str);
//     int count = 0;
//     while(query.next()) {
//         Contact contact;
//         contact.id = count++;
//         contact.name = query.value(2).toString();
//         contact.email = query.value(3).toString();
//         if (contact.name == "")
//             contact.name = contact.email.split("@")[0];
//         contacts.push_back(contact);
//     }
//     return 0;
// }
