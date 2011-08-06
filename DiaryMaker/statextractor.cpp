#include "statextractor.h"
#include "utils.h"

// FIXME: Move me elsewhere
QString STR2(int x)
{
    QString a; a.setNum(x);
    return a;
}

StatExtractor::StatExtractor()
{
    analyser = new SentimentAnalyser();
    done = false;
}

int StatExtractor::initDayList(QList<Day>& dayList)
{
    //FIXME: (Pusing in 10 years arbitrarily (wastage of space) :(
    for (int i = 0 ; i < TEN_YEARS ; i ++ ) {
        Day day;
        day.dayStamp = i;
        dayList.push_back(day);
    }
    return 0;
}

int StatExtractor::extract(QList<Contact> &contacts,QList<Day> &timeStats, QMap<QString, int> &contactsMap, QMap<int, QList<Day> >& userDayMatrix)
{
    completedMessages = 0;
    QList<ChatSmall> chatList;
    QString query = "SELECT * FROM  Messages  WHERE ReplyByChatThreadId LIKE 'replybychat:%'";
    handler->getChats(query, chatList);
    QMap<int, int> impContacts;         // Important contacts
    totalMessages = chatList.size();

    for ( int i = 0 ; i < contacts.size() ; i ++ ) {
        impContacts[i] = 0;
    }

    initDayList(timeStats);
    // Go through all chats
    for(int i = 0 ; i < chatList.size() ; i ++ ) {
        completedMessages ++; 
        ChatSmall chat = chatList.at(i);
        ChatFull full;
        QString start; start.setNum(chatList.at(i).id);
        QString query = "SELECT * FROM MessagesFT_content WHERE rowid="+start;
        handler->getChat(query, full);                  // Get the full chat for analysis

        QString email = full.from.split(" || ").at(1);  // Get the email ID of the friend
        int id = contactsMap[email];                    // Get the friend ID


        // Analyse the chat
        Analysis analysis;
        analyseChat(full.body, analysis);

        // Insert all of the following in the database instead :-)

        // Add to the search index

        // Update the matrices
        if ( impContacts[id] == 0 ) {
            impContacts[id] = 1;
            QList<Day> newDayList;
            initDayList(newDayList);
            userDayMatrix[id] = newDayList;
        }

        // Update the contact
        contacts[id].chatCount ++;                      // Increment chat count for the friend
        contacts[id].timeOfDaty += Utils::getTime(chat.timeInt);
        contacts[id].happiness += analysis.happiness;
        contacts[id].sentiment += analysis.sentiment;
        contacts[id].numChars += analysis.numChars;
        contacts[id].numLines += analysis.numLines;
        contacts[id].totalTime += analysis.totalTime;
        contacts[id].value += analysis.value;

        // Update the day
        int day = Utils::getDayNumber(chat.timeInt);
        timeStats[day].count ++;
        timeStats[day].dayStamp = day;
        timeStats[day].happiness += analysis.happiness;
        timeStats[day].happiness += analysis.happiness;
        timeStats[day].numChars += analysis.numChars;
        timeStats[day].numLines += analysis.numLines;
        timeStats[day].totalTime += analysis.totalTime;
        timeStats[day].value += analysis.value;

        userDayMatrix[id][day].count ++;
        userDayMatrix[id][day].dayStamp = day;
        userDayMatrix[id][day].happiness += analysis.happiness;
        userDayMatrix[id][day].sentiment += analysis.sentiment;
        userDayMatrix[id][day].numChars += analysis.numChars;
        userDayMatrix[id][day].numLines += analysis.numLines;
        userDayMatrix[id][day].totalTime += analysis.totalTime;
        userDayMatrix[id][day].value += analysis.value;
    }
    return 0;
}

int StatExtractor::purify(QString& full, QString& good)
{
    full = QString(full.toAscii());
    good = full.replace("<span style=\"display:block;float:left;color:#888\"> </span>","");
    good = good.replace("<div>","").replace("</div>","").replace("</span>: ",":\n").replace("</span>","\n").replace("<span>","");
    good = good.replace("<span style=\"display:block;float:left;color:#888\">","#TIME# ");
    good = good.replace("<span style=\"font-weight:bold\">","#USER# ");
    good = good.replace("<span style=\"display:block;padding-left:6em\">","");
    good = good.replace("\n#TIME# \n","\n").replace("\n\n","\n");
    good = good.replace("<table cellpadding=\"0\" cellspacing=\"1\"><tr><td style=\"font-size:1;width:100%\"><hr noshade size=\"1\" color=\"#cccccc\"><td nowrap style=\"font-size:80%;color:#aaa\">","#BREAK# ");
    good = good.replace("</td></td></tr></table>","\n").replace("<br>","\n");
    good = good.replace("\n#TIME#  \n","\n");

    return 0;
}

int StatExtractor::analyseChat(QString &full, Analysis &analysis)
{
    // Clean up the chat (remove HTML waste)
    QString good;
    purify(full, good);
    // full = good;
    analysis.numChars = good.length();
    analysis.numLines = good.count("\n")+good.count("<br");
    analyser->analyseOverallSentiment(good, &analysis.sentiment, &analysis.happiness);
    // FIX ME;
    analysis.value = (analysis.numLines*100 - analysis.numChars) ; // * analysis.sentiment;
    return 0;
}

QString StatExtractor::getStatus()
{
    if (completedMessages == totalMessages) {
        return "Done!";
        done = true;
    }

    return "Completed " + STR2(completedMessages) +" out of "+ STR2(totalMessages) + " chats ...";
}
