#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "View/GLView.hpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    GLView * glView = new GLView(this);
    ui->gl_view_layout->addWidget(glView);
}

MainWindow::~MainWindow()
{
    delete ui;
}
