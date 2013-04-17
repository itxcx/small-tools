#include "mainwindow.h"
#include <QTime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    mediaObject = new Phonon::MediaObject(this);
    videoWidget = new Phonon::VideoWidget(this);
    audioOutput = new Phonon::AudioOutput(Phonon::VideoCategory, this);

    Phonon::createPath(mediaObject, audioOutput);
    Phonon::createPath(mediaObject, videoWidget);

    setupActions();
    setupUI();
    connectSignals();
}

MainWindow::~MainWindow()
{
}

void MainWindow::setupActions()
{
    openAction = new QAction("打开文件", this);
    openAction->setShortcut(QKeySequence::Open);
    screenShotAction = new QAction("当前截图", this);
    exitAction = new QAction("退出播放器", this);
    exitAction->setShortcut(QKeySequence::Quit);
    aboutAction = new QAction("关于Bp2", this);
    fullScreeAction = new QAction("全屏观看", this);
}

void MainWindow::setupUI()
{
    hBoxOne      = new QHBoxLayout();
    hBoxTwo      = new QHBoxLayout();
    vBox         = new QVBoxLayout();
    playButton   = new QPushButton(this);
    playNext     = new QPushButton(this);
    playLast     = new QPushButton(this);
    mainWidget   = new QWidget(this);
    seekSlider   = new Phonon::SeekSlider(mediaObject, this);
    volumeSlider = new Phonon::VolumeSlider(audioOutput, this);
    timeLabel    = new QLabel("00:00/00:00", this);
    botOneWidget = new QWidget(this);
    botTwoWidget = new QWidget(this);
    videoPlayList= new playList(this);
    splitter     = new QSplitter(Qt::Horizontal, this);

    QList<int> splitterSize;
    splitterSize << 0 << 160;

    //set style
    playButton->setIcon(QIcon::fromTheme("media-playback-start"));
    playButton->setIconSize(QSize(48, 48));
    playNext->setIcon(QIcon::fromTheme("go-next"));
    playNext->setIconSize(QSize(32, 32));
    playLast->setIcon(QIcon::fromTheme("go-previous"));
    playLast->setIconSize(QSize(32, 32));

    playButton->setStyleSheet("QPushButton{border: none; outline: none;}");
    playNext->setStyleSheet("QPushButton{border: none; outline: none;}");
    playLast->setStyleSheet("QPushButton{border: none; outline: none;}");
    volumeSlider->setMaximumWidth(120);
    volumeSlider->setMinimumWidth(120);
    botOneWidget->setFixedHeight(16);
    botTwoWidget->setFixedHeight(50);

    //set layout
    hBoxOne->addWidget(seekSlider);
    hBoxOne->addWidget(timeLabel);
    hBoxOne->addWidget(volumeSlider);
    hBoxOne->setContentsMargins(0, 0, 0, 0);

    hBoxTwo->addStretch();
    hBoxTwo->addWidget(playLast);
    hBoxTwo->addWidget(playButton);
    hBoxTwo->addWidget(playNext);
    hBoxTwo->addStretch();
    hBoxTwo->setContentsMargins(0, 0, 0, 0);

    botOneWidget->setLayout(hBoxOne);
    botTwoWidget->setLayout(hBoxTwo);

    splitter->addWidget(videoWidget);
    splitter->addWidget(videoPlayList);

    splitter->setStretchFactor(0, 1);
    splitter->setStretchFactor(1, 0);
    splitter->setSizes(splitterSize);
    vBox->addWidget(splitter);
    vBox->addWidget(botOneWidget);
    vBox->addWidget(botTwoWidget);

    mainWidget->setLayout(vBox);
    setCentralWidget(mainWidget);
    vBox->setContentsMargins(0, 0, 0, 0);
    resize(600, 380);
    setWindowTitle("Bp2");
    setWindowIcon(QIcon(":/icon/img/emblem-sound.svg"));

    videoWidget->installEventFilter(this);
}

void MainWindow::connectSignals()
{
    connect(videoPlayList, SIGNAL(playThisFile(QString)), this, SLOT(playThisFile(QString)));
    connect(playButton, SIGNAL(clicked()), this, SLOT(playStatusHandle()));
    connect(playNext, SIGNAL(clicked()), videoPlayList, SLOT(playNext()));
    connect(playLast, SIGNAL(clicked()), videoPlayList, SLOT(playgPrevious()));
    connect(mediaObject, SIGNAL(tick(qint64)), this, SLOT(updateTime(qint64)));
}

bool MainWindow::eventFilter(QObject *obj, QEvent *eve)
{
    if (obj == videoWidget && eve->type() == QEvent::MouseButtonDblClick)
    {
         if (videoWidget->isFullScreen())
        {
            this->show();
            videoWidget->setFullScreen(false);
        }
        else
        {
            this->hide();
            videoWidget->setFullScreen(true);
        }
    }
    else if (obj == videoWidget && eve->type() == QEvent::KeyPress)
    {
        QKeyEvent *ke = static_cast<QKeyEvent *>(eve);
        if ((ke->key() == Qt::Key_Escape) && videoWidget->isFullScreen())
        {
            this->show();
            videoWidget->setFullScreen(false);
        }

    }
    return QMainWindow::eventFilter(obj, eve);
}

void MainWindow::playThisFile(const QString &file)
{
    if (file != "")
    {
        Phonon::MediaSource ms(file);
        mediaObject->setCurrentSource(file);
        videoPlayList->setCurrentPlay(file);
        mediaObject->play();
        setWindowTitle(file);
        playButton->setIcon(QIcon::fromTheme("media-playback-pause"));
    }
}

void MainWindow::playStatusHandle()
{
    if (mediaObject->state() == Phonon::PlayingState)
    {
        mediaObject->pause();
        playButton->setIcon(QIcon::fromTheme("media-playback-start"));
    }
    else if (mediaObject->state() == Phonon::PausedState)
    {
        mediaObject->play();
        playButton->setIcon(QIcon::fromTheme("media-playback-pause"));
    }
    else
    {
        openFile *ofDialog = new openFile(this);
        ofDialog->show();
        connect(ofDialog, SIGNAL(raiseVideoAddr(QString)),
                videoPlayList, SLOT(addVideo(QString)));
        connect(ofDialog, SIGNAL(raiseVideoAddr(QString)),
                this, SLOT(playThisFile(QString)));
        mediaObject->pause();
        playButton->setIcon(QIcon::fromTheme("media-playback-pause"));
    }
}

void MainWindow::updateTime(qint64 time)
{
    qint64 totalTimeValue = mediaObject->totalTime();
    QTime totalTime(0, (totalTimeValue/60000), (totalTimeValue/1000)%60);
    QTime currentTime(0, (time/60000), (time/1000)%60);
    timeLabel->setText(currentTime.toString("mm:ss") + "/" + totalTime.toString("mm:ss"));
}
