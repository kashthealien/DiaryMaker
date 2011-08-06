#include "fileparsers.h"
#include "utils.h"
#include <QFileDialog>

int FileParsers::parseCustomDiary(QString fileName)
{

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return 1;

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        if (line.size() == 0)
            continue;
        else if(line.at(0) == '#')
            continue;

        QStringList attrs = line.split(';');
        QString importance = attrs[2];
        if (attrs[2] == "1" || attrs[2] == " 1") {
            DiaryEvent newEvent;
            int day = Utils::timeInt(attrs[0]);
            newEvent.id = day;
            newEvent.description = attrs[1];
            events[day].push_back(newEvent);
        }
    }
    for (QMap<int, QList<DiaryEvent> >::iterator iter = events.begin() ; iter != events.end() ; iter ++ ) {
        for (int i = 0 ; i < (*iter).size() ; i ++ ) {
            // qDebug() << (*iter)[i].id  << " "<< (*iter)[i].description;
        }
    }
    return 0;
}

int FileParsers::parseFbDiary(QString fileName)
{
    QFile file(fileName);
    QString contents = file.readAll();
    QStringList lines = contents.split("\n");
    for ( int i = 0 ; i < lines.size() ; i ++ ) {
        QString line = lines.at(i);
        QStringList attrs = line.split(",");
        for (int j = 0 ; j < attrs.size() ; j ++ ) {

        }
    }
    return 0;
}

int FileParsers::parseFbFriends(QString fileName)
{
    QFile file(fileName);
    QString contents = file.readAll();
    QStringList lines = contents.split("\n");
    for ( int i = 0 ; i < lines.size() ; i ++ ) {
        QString line = lines.at(i);
        QStringList attrs = line.split(",");
        for (int j = 0 ; j < attrs.size() ; j ++ ) {

        }
    }
    return 0;
}

int FileParsers::parseTwitterDiary(QString fileName)
{
    QFile file(fileName);
    QString contents = file.readAll();
    QStringList lines = contents.split("\n");
    for ( int i = 0 ; i < lines.size() ; i ++ ) {
        QString line = lines.at(i);
        QStringList attrs = line.split(",");
        for (int j = 0 ; j < attrs.size() ; j ++ ) {

        }
    }
    return 0;
}

int FileParsers::facebookDiary()
{
    QString selectedPath = QFileDialog::getOpenFileName(0,
     "Open the Facebook diary files", "", "Diary files (*.kal)");
    return 0;
}

int FileParsers::facebookFriends()
{
     QString selectedPath = QFileDialog::getOpenFileName(0,
     "Open the Facebook friends files", "", "Diary files (*.csv)");
    return 0;
}

int FileParsers::tweetDiary()
{
    QString selectedPath = QFileDialog::getOpenFileName(0,
     "Open the Twitter diary files", "", "Diary files (*.kal)");
    return 0;
}
int FileParsers::customDiary()
{
    QString selectedPath = QFileDialog::getOpenFileName(0,
     "Open the Custom diary entries files", "", "Diary files (*.kal)");
    parseCustomDiary(selectedPath);
    return 0;
}
