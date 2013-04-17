#ifndef OPENFILE_H
#define OPENFILE_H

#include <QDialog>
#include <QTabBar>
#include <QLineEdit>
#include <QTabWidget>
#include <QWidget>
#include <QLayout>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QLabel>
#include <QDesktopServices>
#include <QFileDialog>

class openFile : public QDialog
{
    Q_OBJECT
public:
    explicit openFile(QWidget *parent = 0);
    ~openFile();
    void setupUI();
private:
    QTabWidget *tabWidget;
    QWidget *tabOne;
    QWidget *tabTwo;

    QVBoxLayout *mainLayout;
    QDialogButtonBox *dialogButton;

    //tab One
    QLabel *labelOne;
    QLineEdit *lineEditOne;
    QPushButton *pushButtonOne;
    QGridLayout *tabOneLayout;
    QLabel *tabOneTips;

    //tabTwo;
    QLabel *labelTwo;
    QLineEdit *lineEditTwo;
    QGridLayout *tabTwoLayout;
    QLabel *tabTwoTips;
signals:
    void raiseVideoAddr(QString);
protected slots:
    void accept();
    void fileDialog();
};

#endif // OPENFILE_H
