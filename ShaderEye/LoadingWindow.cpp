#include "LoadingWindow.h"
#include "ui_LoadingWindow.h"
#include "Util/CommonSetting.h"
#include "LoadingWindow.h"
#include <QSettings>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>
#include <MainWindow.h>
#include <QElapsedTimer>

LoadingWindow::LoadingWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoadingWindow)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Tool | Qt::WindowStaysOnTopHint);

    connect(&timer, SIGNAL(timeout()), this, SLOT(timeoutSig()));
    timer.setSingleShot(true);
    timer.start(3000);

    QFont titleFont;
    titleFont.setPointSize(25);
    titleFont.setFamily("黑体");
    titleFont.setBold(true);
    ui->title_label->setFont(titleFont);
    char loadingTitle[100] = {0};
    sprintf(loadingTitle, "ShaderEye %s", STRING_VERSION);
    ui->title_label->setText(loadingTitle);

    QFont subTitleFont;
    subTitleFont.setFamily("黑体");
    // subTitleFont.setBold(true);
    subTitleFont.setPointSize(15);
    ui->sub_title_label->setFont(subTitleFont);


    QImage img;
    img.load(":/img/logo/logo_shadereye.png");
    img = img.scaledToWidth(150, Qt::SmoothTransformation);
    ui->logo_img->setPixmap(QPixmap::fromImage(img));



}

LoadingWindow::~LoadingWindow()
{
    delete ui;
}

void LoadingWindow::timeoutSig() {
    MainWindow * mainWindows = new MainWindow();
    mainWindows->show();

    close();
}
