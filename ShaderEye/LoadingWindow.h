#ifndef LOADINGWINDOW_H
#define LOADINGWINDOW_H

#include <QMainWindow>
#include <QTimer>
//#include <QNetworkReply>

namespace Ui {
class LoadingWindow;
}

class LoadingWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LoadingWindow(QWidget *parent = nullptr);
    ~LoadingWindow();

private:
    Ui::LoadingWindow *ui;

    QTimer timer;

public slots:
    void timeoutSig();
//    void OnNetworkProcessFinished(QNetworkReply *);
};

#endif // LOADINGWINDOW_H
