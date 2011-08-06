#ifndef TUTORIAL_H
#define TUTORIAL_H

#include <QtGui/QDialog>

#include "structs.h"

namespace Ui {
    class Tutorial;
}

class Tutorial : public QDialog {
    Q_OBJECT
public:
    Tutorial(QWidget *parent = 0);
    ~Tutorial();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::Tutorial *m_ui;
    int picNo;
    QPixmap *pix;
    QStringList pics;
    QStringList messages;
private slots:
    int left();
    int right();
};

#endif // TUTORIAL_H
