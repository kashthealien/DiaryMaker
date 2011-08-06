#ifndef SQLITEHANDLER_H
#define SQLITEHANDLER_H
#include <QString>
#include <QSqlDatabase>
#include "structs.h"

class SqliteHandler
{
public:
    SqliteHandler();
    bool createConnection();
    void setPath(QString newPath) {path = newPath;}
    int getChats(QString query, QList<ChatSmall> &chats);
    int getChat(QString query, ChatFull &chat);
    int getContacts1(QString query, QList<Contact>& contacts);
    QSqlDatabase db;

private:
    QString path;
};

#endif // SQLITEHANDLER_H
