#ifndef CHATBROWSER_H
#define CHATBROWSER_H
#include "sqlitehandler.h"

class ChatBrowser
{
private:
    SqliteHandler *handler;
public:
    ChatBrowser();
    QString getChats(QString user, int num = 0);
    QList<QString> getChats(QString user);
    void setHandler(SqliteHandler *handle) {handler = handle;}
    int loadChats(QString limit, int start, int range, QList<ChatSmall>& outList);
    int loadChat(int index, ChatFull& chat);
    int loadContacts(QList<Contact>& contact, QMap<QString, int>& contactMap);
};

#endif // CHATBROWSER_H
