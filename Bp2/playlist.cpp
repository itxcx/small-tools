#include "playlist.h"
#include <QDebug>
#include <QStringListIterator>
playList::playList(QWidget *parent) :
    QWidget(parent)
{
    listWidget = new QListWidget(this);
    add = new QPushButton("+", this);
    del = new QPushButton("-", this);
    mainLayout = new QVBoxLayout(this);
    HLayout = new QHBoxLayout();
    currentFile = "";
    setupUI();
}

playList::~playList()
{}

void playList::setupUI()
{
    add->setMaximumSize(20, 20);
    del->setMaximumSize(20, 20);
    HLayout->setSpacing(0);
    HLayout->addWidget(add);
    HLayout->addWidget(del);
    HLayout->addStretch();
    mainLayout->addWidget(listWidget);
    mainLayout->addLayout(HLayout);
    setLayout(mainLayout);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    listWidget->setCurrentRow(0);

    connect(del, SIGNAL(clicked()), this, SLOT(deleteVideoButton()));
    connect(add, SIGNAL(clicked()), this, SLOT(addVideoDialog()));
    connect(listWidget, SIGNAL(doubleClicked(QModelIndex)),
            this, SLOT(doubleClickedFile(QModelIndex)));
}

void playList::addVideo(const QString& str)
{
    if ((videoList.indexOf(str) == -1) && (str != ""))
    {
        videoList.append(str);
        updateVideoList();
    }
}

void playList::updateVideoList()
{
    listWidget->clear();
    if (!videoList.isEmpty())
    {
        QListIterator<QString>i(videoList);
        QString *tmp;
        while(i.hasNext())
        {
            tmp = const_cast<QString*>(&(i.next()));
            listWidget->addItem(tmp->mid(tmp->lastIndexOf("/") + 1));
        }
    }
}

void playList::deleteVideoButton()
{
    videoList.removeAt(listWidget->currentRow());
    listWidget->clear();
    updateVideoList();
}

void playList::addVideoDialog()
{
    openFile *ofDialog = new openFile(this);
    ofDialog->show();
    connect(ofDialog, SIGNAL(raiseVideoAddr(QString)),
            this, SLOT(addVideo(QString)));
}

void playList::doubleClickedFile(QModelIndex index)
{
    emit playThisFile(videoList.at(index.row()));
}

int playList::getCurrentFocusRow()
{
    return listWidget->currentIndex().row();
}

void playList::playNext()
{
    if (videoList.count() == 0)
        return;
    int pos = videoList.indexOf(currentFile);
    if (pos != -1)
    {
        if (pos == (videoList.count() - 1))
        {
            playThisFile(videoList.first());
            setCurrentPlay(videoList.first());
        }
        else if (pos < (videoList.count() - 1))
        {
            playThisFile(videoList.at(pos + 1));
            setCurrentPlay(videoList.at(pos + 1));
        }
    }
}
void playList::playgPrevious()
{
    if (videoList.count() == 0)
        return;
    int pos = videoList.indexOf(currentFile);
    if (pos != -1)
    {
        if (pos == 0)
        {
            playThisFile(videoList.last());
            setCurrentPlay(videoList.last());
        }
        else
        {
            playThisFile(videoList.at(pos - 1));
            setCurrentPlay(videoList.at(pos - 1));
        }
    }
}

void playList::setCurrentPlay(const QString &file)
{
    int pos = videoList.indexOf(currentFile);
    if (pos != -1)
    {
        listWidget->item(pos)->setIcon(QIcon());
    }

    currentFile = file;
    pos = videoList.indexOf(file);
    if (pos != -1)
    {
        listWidget->item(pos)->setIcon(QIcon(QIcon::fromTheme("media-playback-start")));
    }
}
