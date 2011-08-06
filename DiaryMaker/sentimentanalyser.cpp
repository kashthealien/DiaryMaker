#include "sentimentanalyser.h"

SentimentAnalyser::SentimentAnalyser()
{
    init();
}

int SentimentAnalyser::loadDict(QMap<QString, float>& dict, QString fileName)
{
    QFile file(fileName);
     if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
         return 1;

     QTextStream in(&file);
     while (!in.atEnd()) {
         QString line = in.readLine();
         // qDebug() << line;
         QStringList lexicon = line.split("\t");
         QString word = lexicon.at(0);
         QString val = lexicon.at(1);
         float value = val.toFloat();
         dict[word] = value;
     }
     return 0;
}
int SentimentAnalyser::loadSet(QSet<QString>& set, QString fileName)
{
    QFile file(fileName);
     if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
         return 1;

     QTextStream in(&file);
     while (!in.atEnd()) {
         QString line = in.readLine();
         set.insert(line);
     }
     return 0;
}

int SentimentAnalyser::init()
{
    // Load the booseter words
    loadDict(boosters,BOOSTERS_PATH);
    // Load the emotion words
    loadDict(emotions,EMOTIONS_PATH);
    // Load negators
    loadSet(negators, NEGATORS_PATH);
    // Load emoticons
    loadDict(emoticon,EMOTICON_PATH);

    return 0;
}

int SentimentAnalyser::analyseSentiment(const QString &line, float *value)
{
    float val = 0.0;
    // QRegExp reg("( |.|,|!|-|&)");
    QStringList words = line.split(" ");
    bool negate = false;
    float modify = 0.0;
    for ( int i = 0 ; i < words.size() ; i ++ ) {
        QString word = words.at(i);
        if (emotions.contains(word)) {
            val += emotions[word];
        }
        if (negators.contains(word))
            negate = ! negate;
        if (boosters.contains(word)) {
            float mod = boosters[word];
            modify += mod;
        }
    }
    val += modify;
    if(negate) {
        val = -val;
    }
    *value = val;
    return 0;
}
int SentimentAnalyser::analyseSentiments(QString &text, QList<float> &sentiments)
{
    QStringList sentences = text.split("\n");
    sentiments.clear();
    for ( int i = 0 ; i < sentences.size() ; i ++ ) {
        float val;
        analyseSentiment(sentences.at(i), &val);
        sentiments.push_back(val);
    }
    return 0;
}

int SentimentAnalyser::analyseOverallSentiment(QString &text, float* senti, float* happy)
{
    QList<float> sentiments;
    analyseSentiments(text, sentiments);
    * senti = 0.0;
    * happy = 0.0;
    for (int i = 0 ; i < sentiments.size() ; i ++ ) {
        float temp = sentiments.at(i);
        *senti += (temp>0)?(temp):(-temp);
        *happy += temp;
    }
    // TODO Remove me!
    * senti = 0.0;
    * happy = 0.0;
    return 0;
}
