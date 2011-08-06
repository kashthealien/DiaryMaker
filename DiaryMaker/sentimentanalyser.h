#ifndef SENTIMENTANALYSER_H
#define SENTIMENTANALYSER_H

// FIXME: Remove these definitions already there in "structs.h"
#include "structs.h"
#include <QDebug>
#include <QVector>
#include <QString>
#include <QList>
#include <QFile>
#include <QStringList>

class SentimentAnalyser
{
public:
    SentimentAnalyser();
    int analyseSentiments(QString &text, QList<float> &sentiments);
    int analyseOverallSentiment(QString &text, float* senti, float* happy);
private:
    QMap<QString, float> emotions;
    QMap<QString, float> emoticon;
    QMap<QString, float> boosters;
    QSet<QString> negators;

    int analyseSentiment(const QString &text, float* value);
    int loadDict(QMap<QString, float>& dict, QString fileName);
    int loadSet(QSet<QString>& set, QString fileName);
    int init();
};

#endif // SENTIMENTANALYSER_H
