#include "MainWindow.h"
#include <QApplication>
#include <QSurfaceFormat>
#include <QSplashScreen>
#include "LoadingWindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    format.setStencilBufferSize(8);
    format.setVersion(3, 3);
    format.setProfile(QSurfaceFormat::CoreProfile);
    QSurfaceFormat::setDefaultFormat(format);

//    MainWindow w;
//    w.show();

    LoadingWindow loading;
    loading.show();

    return a.exec();
}
