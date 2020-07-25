#ifndef COMPILEINFOWINDOW_H
#define COMPILEINFOWINDOW_H

#include <QMainWindow>

namespace Ui {
class CompileInfoWindow;
}

class CompileInfoWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CompileInfoWindow(QWidget *parent = nullptr);
    ~CompileInfoWindow();
    void setCompileLog(QString compileLog);

private:
    QString m_compileLogInfo;

private slots:
    void OKBtnClick();

private:
    Ui::CompileInfoWindow *ui;
};

#endif // COMPILEINFOWINDOW_H
