#include "diary.h"
#include "ui_diary.h"

#include <QLineEdit>
#include <QSpacerItem>
#include <QFileDialog>
#include <QRadioButton>
#include <QTableWidgetItem>
#include <qwt-qt4/qwt_legend.h>
#include <QColor>
#include <qwt_plot_grid.h>

Diary::Diary(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::Diary)
{
    ui->setupUi(this);

    // Create class instances
    sqlite = new SqliteHandler();
    chatBr = new ChatBrowser();
    statEx = new StatExtractor();
    tute = new Tutorial();
    parser = new FileParsers();
    plotter = new Plotter();
    ui->plotter->setContextMenuPolicy(Qt::CustomContextMenu);
    picker = new QwtPlotPicker(ui->plotter->xBottom,ui->plotter->yLeft,
                     QwtPicker::AlwaysOn, QwtPlotPicker::NoRubberBand, QwtPlotPicker::AlwaysOn,ui->plotter->canvas());

    indexer = new Indexer();
    indexer->setStatExtractor(statEx);
    indexerTimer = new QTimer(this);

    chatBr->setHandler(sqlite);
    statEx->setHandler(sqlite);


    // Find files
    connect(ui->findAuto, SIGNAL(clicked()), this, SLOT(findAuto()));
    connect(ui->findFile, SIGNAL(clicked()), this, SLOT(findFile()));
    // Load chat
    connect(ui->chats, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(loadChat(QModelIndex)));
    connect(ui->contactsList, SIGNAL(currentIndexChanged(int)), this, SLOT(loadChats()));
    // Paging left and right for chats
    connect(ui->left, SIGNAL(clicked()), this, SLOT(decrIndex()));
    connect(ui->right, SIGNAL(clicked()), this, SLOT(incrIndex()));
    // Refresh the whole app
    // connect(ui->refresh, SIGNAL(clicked()), this, SLOT(refresh()));
    // Plotting
    connect(ui->contactsList2, SIGNAL(currentIndexChanged(int)), this, SLOT(replot()));
    connect(ui->plotOptions, SIGNAL(currentIndexChanged(int)), this, SLOT(replot()));
    connect(ui->smoother,SIGNAL(sliderMoved(int)), this, SLOT(setWindowSize(int)));
    connect(picker, SIGNAL(selected(QwtDoublePoint)), this, SLOT(plotDescribe(QwtDoublePoint)));
    connect(ui->toggleCal, SIGNAL(toggled(bool)), this, SLOT(toggleCalendar(bool)));
    connect(ui->incrDate, SIGNAL(clicked()), this, SLOT(incrTrendsDate()));
    connect(ui->decrDate, SIGNAL(clicked()), this, SLOT(decrTrendsDate()));
    // Help
    connect(ui->offlineGmailHelp, SIGNAL(clicked()), tute, SLOT(show()));
    // Additional
    connect(ui->facebook, SIGNAL(clicked()), parser, SLOT(facebookDiary()));
    connect(ui->twitter, SIGNAL(clicked()), parser, SLOT(tweetDiary()));
    connect(ui->facebookFriends, SIGNAL(clicked()), parser, SLOT(facebookFriends()));
    connect(ui->customDiary, SIGNAL(clicked()), parser, SLOT(customDiary()));
    // Indexing
    connect(this->indexerTimer, SIGNAL(timeout()), this, SLOT(updateIndexingStatus()));

    ui->tabWidget->setCurrentIndex(0);
    ui->smoother->setMaximum(MAX_WINDOW_SIZE);

    // Plotting
    plotSetup();
    displayCalendar = false;

    // Table set up
    QHeaderView * header = ui->chats->horizontalHeader();
    header->setStretchLastSection(true);


    // Paging parameters
    chatIndex = 0;
    jumpValue = 50;
}

Diary::~Diary()
{
    delete ui;
}

int Diary::plotSetup()
{
    // Background
    ui->plotter->setCanvasBackground(QColor(Qt::white));
    ui->plotter->setMargin(5);

    // legend
    QwtLegend *legend = new QwtLegend;
    legend->setFrameStyle(QFrame::Box|QFrame::Sunken);
    ui->plotter->insertLegend(legend, QwtPlot::BottomLegend);

    // New curve
    newCurve = new QwtPlotCurve();
    newCurve->setPen(QPen(Qt::red));
    newCurve->attach(ui->plotter);

    calCurve = new QwtPlotCurve();
    calCurve->setPen(QPen(Qt::green));
    calCurve->setStyle(QwtPlotCurve::Sticks);
    calCurve->attach(ui->plotter);

    // Grids
    /*
        QwtPlotGrid *gridy = new QwtPlotGrid();
        gridy->attach(ui->plotter);
    */

    return 0;
}
int Diary::replot()
{
    plot(1);
    return 0;
}

int Diary::toggleCalendar(bool val)
{
    displayCalendar = val;
    plot(1);
    return 0;
}

int Diary::calendarEvents()
{
    QVector<double> calX, calY;
    if(displayCalendar) {

        int minx = newCurve->minXValue();
        int maxx = newCurve->maxXValue();
        int maxy = newCurve->maxYValue() + 100.0;
        for (int i = minx ; i <= maxx ; i ++ ) {
            QList<DiaryEvent> events = parser->getEvents(i);
            if (events.size() != 0) {
                calX.push_back(i);
                calY.push_back(maxy);
            }
        }
    }
    calCurve->setData(calX,calY);
    ui->plotter->replot();
    return 0;
}

int Diary::plot(int replot = 1)
{
    /*
    if (x.size() == 0)
        return 0;
    */
    int option = ui->plotOptions->currentIndex();
    if (replot) {
        switch(option)
        {
            case 0:
                plotLength();
                calendarEvents();
                break;
            case 1:
                plotSenti();
                calendarEvents();
                break;
        }
    }
    if (x.size() > 0 ) {
        QVector<double> smoothY;
        plotter->smooth1(y, smoothY);
        newCurve->setData(x,smoothY);
        ui->plotter->replot();
    }
    return 0;
}

int Diary::plotLength()
{
    ui->plotter->setTitle("Plotting Chat lengths");
    // axis
    ui->plotter->setAxisTitle(QwtPlot::xBottom, "Time");
    ui->plotter->setAxisTitle(QwtPlot::yLeft, "Length Lines");

    // Data
    x.clear(); y.clear();
    QString user = ui->contactsList2->currentText().split(" ").back();
    int i = 0;
    if (user == "All") {
        while (i < timeStats.size() && timeStats[i].numLines == 0) {
            i ++;
        }
        for ( ; i < timeStats.size() ; i ++ ) {
            // x.append(count++);
            x.append(i);
            y.append(timeStats[i].numChars);

        }
    } else {
        int userId = contactsMap[user];
        while (i < usersDays[userId].size() && usersDays[userId][i].numLines == 0) {
            i ++;
        }
        for ( ; i < usersDays[userId].size() ; i ++ ) {
            // x.append(count++);
            x.append(i);
            y.append(usersDays[userId][i].numChars);
        }

    }
    while (y.size() > 0 && y.back() == 0) {
            y.pop_back(); x.pop_back();
    }
    if (x.size() > 0 ) {
        trendsDate = x.front();
    } else {
        trendsDate = 0;
    }
    newCurve->setTitle("Chat length Versus time");
    return 0;
}

int Diary::plotSenti()
{
    ui->plotter->setTitle("Plotting Sentiments");
    // axis
    ui->plotter->setAxisTitle(QwtPlot::xBottom, "Time");
    ui->plotter->setAxisTitle(QwtPlot::yLeft, "Sentiment value");
    QString user = ui->contactsList2->currentText().split(" ").back();
    // Data
    QVector<double> x, y;
    int i = 0;
    if (user == "All") {
        while(i < timeStats.size() && timeStats[i].numLines == 0) {
            i ++;
        }
        for ( ; i < timeStats.size() ; i ++ ) {
            // x.append(count++);
            x.append(i);
            y.append(timeStats[i].sentiment);
        }
    } else {
        int userId = contactsMap[user];
        while(i < usersDays[userId].size() && usersDays[userId][i].numLines == 0) {
            i ++;
        }
        for ( ; i < usersDays[userId].size() ; i ++ ) {
            // x.append(count ++);
            x.append(i);
            y.append(timeStats[i].sentiment);
        }
    }
    while (y.size() > 0 && y.back() == 0) {
        y.pop_back(); x.pop_back();
    }
    if (x.size() > 0 ) {
        trendsDate = x.front();
    } else {
        trendsDate = 0;
    }
    newCurve->setTitle("Chat sentiment Versus time");
    return 0;
}

int Diary::plotDescribe(QwtDoublePoint point)
{
    int dayNum = (int)point.x();
    trendsDate = dayNum;
    updateTrends();
    return 0;
}

int Diary::incrTrendsDate()
{
    if (trendsDate == TEN_YEARS-1) {
        return 0;
    }
    trendsDate = trendsDate + 1;
    updateTrends();
    return 0;
}

int Diary::decrTrendsDate()
{
    if (trendsDate == 0) {
        return 0;
    }
    trendsDate = trendsDate - 1;
    updateTrends();
    return 0;
}

int Diary::updateTrends()
{
    if (x.size() == 0)
        return 0;
    int dayNum = trendsDate;
    QList<DiaryEvent> events = parser->getEvents(dayNum);
    QString eventsText;
    for (int i = 0 ; i < events.size() ; i ++ ) {
        eventsText += events[i].description+"\n";
    }
    QString user = ui->contactsList2->currentText().split(" ").back();
    Day day;
    if (user == "All") {
        day = timeStats[dayNum];
    } else {
        int userId = contactsMap[user];
        day = usersDays[userId][dayNum];
    }

    ui->trendsDate->setText(Utils::timeStr(Utils::getTimeStamp(day.dayStamp)));
    ui->trendsHappiness->setText(Utils::STR(day.happiness));
    ui->trendsLines->setText(Utils::STR(day.numLines));
    ui->trendsValue->setText(Utils::STR(day.value));
    ui->trendsSentiment->setText(Utils::STR(day.sentiment));
    ui->trendsEvents->setText(eventsText);
    return 0;
}

int Diary::setWindowSize(int x)
{
    plotter->setWindowSize(x);
    plot(0);
    return 0;
}

int Diary::loadContacts()
{
    contacts.clear();
    chatBr->loadContacts(contacts, contactsMap);
    return 0;
}

int Diary::showContacts()
{
    chatBuddies.clear();
    for ( int i = 0 ; i < contacts.size() ; i ++ ) {
        if (contacts.at(i).chatCount > 0) {
            chatBuddies.push_back(contacts.at(i));
        }
    }
    ui->contacts->setRowCount(chatBuddies.size());
    for ( int i = 0 ; i < chatBuddies.size() ; i ++ ) {
        ui->contactsList2->addItem(chatBuddies[i].name + " " + chatBuddies[i].email);
        ui->contactsList ->addItem(chatBuddies[i].name + " " + chatBuddies[i].email);
        QTableWidgetItem *item1 = new QTableWidgetItem();
        item1->setData(0, chatBuddies[i].name);
        item1->setFlags(Qt::ItemIsEnabled|Qt::ItemIsSelectable);
        ui->contacts->setItem(i, 0, item1);
        QTableWidgetItem *item2 = new QTableWidgetItem();
        item2->setData(0, chatBuddies[i].email);
        item2->setFlags(Qt::ItemIsEnabled|Qt::ItemIsSelectable);
        ui->contacts->setItem(i, 1, item2);
        QTableWidgetItem *item3 = new QTableWidgetItem();
        item3->setData(0, chatBuddies[i].chatCount);
        item3->setFlags(Qt::ItemIsEnabled|Qt::ItemIsSelectable);
        ui->contacts->setItem(i, 2, item3);
        QTableWidgetItem *item4 = new QTableWidgetItem();
        item4->setData(0, chatBuddies[i].numLines);
        item4->setFlags(Qt::ItemIsEnabled|Qt::ItemIsSelectable);
        ui->contacts->setItem(i, 3, item4);
        QTableWidgetItem *item5 = new QTableWidgetItem();
        item5->setData(0, chatBuddies[i].value);
        item5->setFlags(Qt::ItemIsEnabled|Qt::ItemIsSelectable);
        ui->contacts->setItem(i, 4, item5);

    }
    return 0;
}

int Diary::loadChats()
{
    QList<ChatSmall> outList;
    QString user = ui->contactsList->currentText().split(" ").back();
    chatBr->loadChats(user ,chatIndex, jumpValue, outList);
    currentChats = outList;
    ui->chats->clear();
    ui->chats->setRowCount(outList.size());
    for( int i = 0 ; i < outList.size() ; i ++ ) {
        QTableWidgetItem* item1 = new QTableWidgetItem(outList.at(i).time);
        item1->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        ui->chats->setItem(i,0,item1);
        QTableWidgetItem* item2 = new QTableWidgetItem(outList.at(i).snippet);
        item2->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        ui->chats->setItem(i,1,item2);
    }
    return 0;
}

int Diary::loadChat(QModelIndex qm)
{

    int index = qm.row();
    loadChat(index);
    ui->tabWidget->setCurrentIndex(2);
    return 0;
}

int Diary::loadChat(int index_)
{
    int chatID = this->currentChats[index_].id;
    Analysis analysis;
    ChatFull outChat;
    chatBr->loadChat(chatID, outChat);
    statEx->analyseChat(outChat.body,analysis);
    currentChat = outChat;
    ui->subjChat->setText(outChat.subj);
    ui->fromChat->setText(outChat.from);
    ui->toChat->setText(outChat.to);
    ui->chat->setText(outChat.body);
    ui->chatLength->setText(Utils::STR(analysis.numChars)+" Characters"+Utils::STR(analysis.numLines)+" Lines");
    ui->chatScore->setText(Utils::STR(analysis.value));
    ui->chatHappiness->setText(Utils::STR(analysis.happiness));
    ui->chatSentiment->setText(Utils::STR(analysis.sentiment));

    return 0;
}

int Diary::incrIndex()
{
    chatIndex += jumpValue;
    loadChats();
    ui->chatIndex->setText(Utils::STR(chatIndex));
    return 0;
}

int Diary::decrIndex()
{
    if (chatIndex == 0)
        return 0;
    else {
        chatIndex -= jumpValue;
        loadChats();
        ui->chatIndex->setText(Utils::STR(chatIndex));
    }
    return 0;
}


int Diary::findAuto()
{
    QString location = Utils::getLocation();
    selectedPath = QFileDialog::getOpenFileName(0, "Open {emailID}#database", location, "Database files (*#database)");
    sqlite->setPath(selectedPath);
    if(sqlite->createConnection()) {
        if( !profiles.contains(selectedPath)) {
            profiles.push_back(selectedPath);
            ui->list->insertItem(ui->list->count(),selectedPath);
            refresh();
        }
    }
    return 0;
}

int Diary::findFile()
{
    selectedPath = QFileDialog::getOpenFileName(0,
     "Open the database file", "", "Database files (*#database)");
    sqlite->setPath(selectedPath);
    if(sqlite->createConnection()) {
        if( !profiles.contains(selectedPath)) {
            profiles.push_back(selectedPath);
            ui->list->insertItem(ui->list->count(),selectedPath);
            refresh();
        }
    }    
    return 0;
}

int Diary::refresh()
{
    chatIndex = 0;
    // try {
        loadChats();
        loadChat(0);
        loadContacts();
        startIndexing();
        showContacts();
        ui->tabWidget->setCurrentIndex(1);
    // } catch(...) {
    // }

    return 0;
}

int Diary::updateIndexingStatus()
{
    QString message = this->statEx->getStatus();
    if (message == "Done!" ){
        stopIndexing();
    }
    ui->statusBar->showMessage(message, 2000);
    return 0;
}

int Diary::startIndexing()
{
     indexerTimer->start(1000);
     indexer->setContacts(contacts, contactsMap);
     indexer->setStats(timeStats, usersDays);
     indexer->start();
     return 0;
}

int Diary::stopIndexing()
{
    indexer->getContacts(contacts, contactsMap);
    indexer->getTimeStats(timeStats, usersDays);
    indexerTimer->stop();
    showContacts();
    plot(1);
    return 0;
}
