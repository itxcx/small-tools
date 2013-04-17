#include "mainwindow.h"
#include "openfile.h"
#include "playlist.h"
#include <QApplication>
#include <QTextCodec>
#include <QDesktopWidget>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("Bp2");

    QTextCodec *codec = QTextCodec::codecForName("system");
    QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForLocale(codec);
    QTextCodec::setCodecForTr(codec);

    MainWindow w;
    w.show();
    w.move((QApplication::desktop()->width()  - w.width())/2,
           (QApplication::desktop()->height() - w.height())/2);
    
    return a.exec();
}
