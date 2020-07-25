#include "CompileInfoWindow.h"
#include "ui_CompileInfoWindow.h"

CompileInfoWindow::CompileInfoWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CompileInfoWindow)
{
    ui->setupUi(this);
    connect(ui->OKBtn, SIGNAL(clicked()), this, SLOT(OKBtnClick()));
}

CompileInfoWindow::~CompileInfoWindow()
{
    delete ui;
}

void CompileInfoWindow::setCompileLog(QString compileLog) {
    m_compileLogInfo = compileLog;
    ui->logTextEdit->setPlainText(m_compileLogInfo);
}

void CompileInfoWindow::OKBtnClick() {
    m_compileLogInfo.clear();
    close();
}
