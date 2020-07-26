#include "AboutWindow.h"
#include "ui_AboutWindow.h"
#include "Util/CommonSetting.h"
#include <QUrl>
#include <QDesktopServices>
//#include <QMessageBox>

AboutWindow::AboutWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AboutWindow)
{
    ui->setupUi(this);
    this->setWindowTitle(STRING_ABOUT);

//    QFont titleFont;
//    titleFont.setPointSize(30);
//    titleFont.setFamily("黑体");
//    titleFont.setBold(true);
//    ui->title_label->setFont(titleFont);
//    ui->url_label->setText(("<a style='color:blue;' href='http://www.realrace.cn'>http://www.realrace.cn</a>"));
//    connect(ui->url_label,SIGNAL(linkActivated(QString)),this,SLOT(openUrl(QString)));

    char verTitle[100] = {0};
    sprintf(verTitle, "YuvEye %s", STRING_VERSION);
    ui->versionLabel->setText(verTitle);

    ui->introTextBrowser->setOpenLinks(false);
    connect(ui->introTextBrowser, SIGNAL(anchorClicked(const QUrl&)),this, SLOT(openUrl(const QUrl&)));
//    connect(ui->introTextBrowser,SIGNAL(clicked(QString)),this,SLOT(openUrl(QString)));

//    // 日志
//    logMan = new LogManager();
//    logMan->RecordOpenAboutDev();
}

AboutWindow::~AboutWindow()
{
    delete ui;
    //delete logMan;
//    logMan = nullptr;
}

void AboutWindow::openUrl(const QUrl& url)
{
    qDebug("open url: %s",url.toString().toStdString().data());
//    logMan->RecordClickAboutRealrace();
    QDesktopServices::openUrl(url);
}
