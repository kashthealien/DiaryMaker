#include "tutorial.h"
#include "ui_tutorial.h"
#include <qdir.h>

Tutorial::Tutorial(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::Tutorial)
{
    m_ui->setupUi(this);
    connect(this->m_ui->left, SIGNAL(clicked()), this, SLOT(left()));
    connect(this->m_ui->right, SIGNAL(clicked()), this, SLOT(right()));
    connect(this->m_ui->ok, SIGNAL(clicked()), this, SLOT(accept()));
    QString currentDir = QDir::currentPath();
    qDebug() << currentDir+TUTE_PATH_1;
    pics.push_back(currentDir+TUTE_PATH_1);
    pics.push_back(currentDir+TUTE_PATH_2);
    pics.push_back(currentDir+TUTE_PATH_3);
    messages.push_back(TUTE_MESG_1);
    messages.push_back(TUTE_MESG_2);
    messages.push_back(TUTE_MESG_3);

    pix = new QPixmap(pics.at(0));
    m_ui->pic->setPixmap(*pix);
    m_ui->Message->setText(messages.at(0));
    picNo = 0;
}

Tutorial::~Tutorial()
{
    delete m_ui;
}

int Tutorial::left()
{
    m_ui->right->setEnabled(true);
    picNo --;
    if( picNo == 0) {
        m_ui->left->setEnabled(false);        
    }
    m_ui->Message->setText(messages.at(picNo));
    delete(pix);
    pix = new QPixmap(pics[picNo]);
    m_ui->pic->setPixmap(*pix);
    return 0;
}

int Tutorial::right()
{
    m_ui->left->setEnabled(true);
    picNo ++;
    if( picNo == MAX_TUTE_PICS-1) {
        m_ui->right->setEnabled(false);
    }
    m_ui->Message->setText(messages.at(picNo));
    delete(pix);
    pix = new QPixmap(pics[picNo]);
    m_ui->pic->setPixmap(*pix);
    return 0;
}

void Tutorial::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        m_ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
