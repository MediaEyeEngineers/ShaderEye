#include "DialogCompileLogWindow.h"
#include "ui_DialogCompileLogWindow.h"

DialogCompileLogWindow::DialogCompileLogWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogCompileLogWindow)
{
    ui->setupUi(this);
}

DialogCompileLogWindow::~DialogCompileLogWindow()
{
    delete ui;
}
