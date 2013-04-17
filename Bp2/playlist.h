#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <QWidget>
#include <QList>
#include <QMap>
#include <QListWidget>
#include <QListWidgetItem>
#include <QList>
#include <QStringList>
#include <QVBoxLayout>
#include <QPushButton>
#include <QSizePolicy>
#include "openfile.h"

class playList : public QWidget
{
    Q_OBJECT
public:
    explicit playList(QWidget *parent = 0);
    int getCurrentFocusRow();
    void setCurrentPlay(const QString &file);
    ~playList();
    
private:
    void setupUI();
    QStringList videoList;
    QVBoxLayout *mainLayout;
    QHBoxLayout *HLayout;
    QPushButton *del;
    QPushButton *add;
    QListWidget *listWidget;

    QString currentFile;
public slots:
    void addVideo(const QString&);
    void updateVideoList();
    void deleteVideoButton();
    void addVideoDialog();
    void doubleClickedFile(QModelIndex);
    void playgPrevious();
    void playNext();
signals:
    void playThisFile(const QString&);
};

#endif // PLAYLIST_H
