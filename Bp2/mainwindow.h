#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <phonon/MediaObject>
#include <phonon/MediaSource>
#include <phonon/SeekSlider>
#include <phonon/VolumeSlider>
#include <phonon/AudioOutput>
#include <phonon/VideoWidget>
#include <QLabel>
#include "openfile.h"
#include "playlist.h"
#include <QSplitter>
#include <QEvent>
#include <QKeyEvent>

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    //Phonon
    Phonon::MediaObject  *mediaObject;
    Phonon::AudioOutput  *audioOutput;
    Phonon::SeekSlider   *seekSlider;
    Phonon::VolumeSlider *volumeSlider;
    Phonon::VideoWidget  *videoWidget;

    //UI
    QHBoxLayout *hBoxOne;
    QHBoxLayout *hBoxTwo;
    QVBoxLayout *vBox;
    QPushButton *playButton;
    QPushButton *playNext;
    QPushButton *playLast;
    QWidget     *mainWidget;
    QWidget     *botOneWidget;
    QWidget     *botTwoWidget;
    QLabel      *timeLabel;
    playList    *videoPlayList;
    QSplitter   *splitter;

    //Actions & Menu
    QAction *openAction;
    QAction *screenShotAction;
    QAction *fullScreeAction;
    QAction *exitAction;
    QAction *aboutAction;

    //function
    void setupUI();
    void setupActions();
    void connectSignals();

protected:
    bool eventFilter(QObject *obj, QEvent *eve);
protected slots:
    void playThisFile(const QString &file);
    void playStatusHandle();
    void updateTime(qint64);
};

#endif // MAINWINDOW_H
