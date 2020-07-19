#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "View/GLView.hpp"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    GLView * glView = new GLView(this);
    ui->RenderLayout->addWidget(glView);

    dlgCameraControl = new DlgSettingCamera(this);
    connect(ui->CameraBtn, SIGNAL(clicked()), this, SLOT(mainCameraOpenClick()));
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::mainCameraOpenClick() {
    dlgCameraControl->exec();
}
