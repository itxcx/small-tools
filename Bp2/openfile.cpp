#include "openfile.h"
#include <QDialogButtonBox>
#include <QDebug>

openFile::openFile(QWidget *parent) :
    QDialog(parent)
{
    setupUI();
}

openFile::~openFile()
{}

void openFile::setupUI()
{
    tabWidget = new QTabWidget(this);
    tabOne = new QWidget(this);
    tabTwo = new QWidget(this);

    // tab one
    labelOne = new QLabel("<b>选择一个本地的文件</b>", tabOne);
    lineEditOne = new QLineEdit(tabOne);
    pushButtonOne = new QPushButton("浏览...", tabOne);
    tabOneTips = new QLabel("<font color=gray size='-1'>选择一个视频文件<br>"
                            "比如扩展名为mp4、avi的文件</font>", tabOne);
    tabOneLayout = new QGridLayout();
    tabOneLayout->addWidget(labelOne, 0, 0, Qt::AlignVCenter);
    tabOneLayout->addWidget(lineEditOne, 1, 0, Qt::AlignVCenter);
    tabOneLayout->addWidget(pushButtonOne, 1, 1, Qt::AlignVCenter);
    tabOneLayout->addWidget(tabOneTips, 2, 0, Qt::AlignVCenter);
    tabOne->setLayout(tabOneLayout);

    // tab Two
    labelTwo = new QLabel("<b>请输入网络视频的URL</b>", tabTwo);
    lineEditTwo = new QLineEdit(tabTwo);
    tabTwoTips = new QLabel("<font color=gray size='-1'>输入网络文件的URL<br>"
                            "比如http://example.com/video.avi</font>", tabTwo);
    tabTwoLayout = new QGridLayout();
    tabTwoLayout->addWidget(labelTwo, 0, 0, Qt::AlignVCenter);
    tabTwoLayout->addWidget(lineEditTwo, 1, 0, Qt::AlignVCenter);
    tabTwoLayout->addWidget(tabTwoTips, 2, 0, Qt::AlignVCenter);
    tabTwo->setLayout(tabTwoLayout);


    tabWidget->addTab(tabOne, QIcon(":/icon/img/my_videos_2.png"), "本地文件");
    tabWidget->addTab(tabTwo, QIcon(":/icon/img/internet.png"), "网络文件");
    dialogButton = new QDialogButtonBox(QDialogButtonBox::Ok|QDialogButtonBox::Cancel,
                                        Qt::Horizontal, this);
    dialogButton->button(QDialogButtonBox::Ok)->setText("确定(&O)");
    dialogButton->button(QDialogButtonBox::Cancel)->setText("取消(&C)");
    mainLayout = new QVBoxLayout();
    mainLayout->addWidget(tabWidget);
    mainLayout->addWidget(dialogButton);
    setLayout(mainLayout);

    setWindowTitle("选择一个文件...");
    resize(420, 240);
    connect(dialogButton, SIGNAL(rejected()), this, SLOT(reject()));
    connect(dialogButton, SIGNAL(accepted()), this, SLOT(accept()));
    connect(pushButtonOne, SIGNAL(clicked()), this, SLOT(fileDialog()));
}

void openFile::accept()
{
    //qDebug() << "accept";
    if (tabWidget->currentIndex() == 0)
        emit raiseVideoAddr(lineEditOne->text());
    else
        emit raiseVideoAddr(lineEditTwo->text());
    QDialog::accept();
}

void openFile::fileDialog()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                           "Choose video",
                           QDesktopServices::storageLocation(QDesktopServices::HomeLocation),
                           "Videos (*.mp4 *.avi *.flv *.rm *.rmvb *.3gp)");
    lineEditOne->setText(fileName);
}
