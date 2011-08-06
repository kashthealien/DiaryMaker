#include "chatbrowser.h"
#include <QList>

// FIXME: Move me elsewhere
QString STR1(int x)
{
    QString a; a.setNum(x);
    return a;
}

ChatBrowser::ChatBrowser()
{

}

int ChatBrowser::loadChats(QString user, int chatIndex,int jumpValue, QList<ChatSmall>& outList)
{
    QString query;
    if (user == "ALL") {
        query = "SELECT * FROM Messages WHERE ReplyByChatThreadId LIKE 'replybychat%' LIMIT " +STR1(chatIndex) +", "+STR1(jumpValue);
    } else {
        query = "SELECT m.*, c.c3FromAddressEmail FROM Messages m, MessagesFT_content c WHERE m.MessageId = c.rowid AND c.c3FromAddressEmail='"+user+"'AND m.ReplyByChatThreadId LIKE 'replybychat%' LIMIT " +STR1(chatIndex) +", "+STR1(jumpValue);
    }
    handler->getChats(query, outList);
    return 0;
}

int ChatBrowser::loadChat(int index, ChatFull& chat)
{
    QString query = "SELECT * FROM MessagesFT_content WHERE rowid="+STR1(index);
    handler->getChat(query, chat);
    chat.id = index;
    return 0;
}

int ChatBrowser::loadContacts(QList<Contact>& contacts, QMap<QString, int>& contactMap)
{
    QString query = "SELECT * FROM Contacts";
    handler->getContacts1(query, contacts);
    for (int i = 0 ; i < contacts.size() ; i ++ ) {
        contactMap[contacts.at(i).email] = contacts.at(i).id;
    }
    return 0;
}

