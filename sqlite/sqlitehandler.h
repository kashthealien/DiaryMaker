#ifndef SQLITEHANDLER_H
#define SQLITEHANDLER_H
#include <QString>
#include <QSet>
#include <QSqlDatabase>

class SqliteHandler
{
public:
    SqliteHandler();
    bool openDB();
    bool createConnection();
    void setPath(QString newPath) {path = newPath;}

    int createTable(void);
    int insertWord(QString query);
    
    int getFiles(QString query, QSet<int> &files);
    
/*    int getChats(QString query, QList<ChatSmall> &chats);
    int getChat(QString query, ChatFull &chat);
    int getContacts1(QString query, QList<Contact>& contacts); */
    QSqlDatabase db;

private:
    QString path;
};

#endif // SQLITEHANDLER_H

/*
query =  "SELECT * FROM MessagesFT_content LIMIT " + start+", 1";
handler->getChat(query, full);                  // Get the full chat for analysis
*/
