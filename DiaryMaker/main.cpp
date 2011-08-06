#include <QtGui/QApplication>
#include "diary.h"
#include <QDebug>
/*
 * TODO
 * 3.> Complete the autofind part
 */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qDebug() << QCoreApplication::libraryPaths();
    Diary w;
    // w.show();
    //w.showFullScreen();
    w.show();
    // w.showMaximized();
    return a.exec();
}
