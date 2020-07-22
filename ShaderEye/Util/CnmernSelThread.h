#ifndef CANMERNSELTHREAD_H
#define CANMERNSELTHREAD_H
/**
 * @date 2020/07/20
 * @author changyanlong github.com/numberwolf q531365872
 */

#include <QDebug>
#include <QString>
#include <QObject>
#include <QCamera>
#include <QCameraInfo>
#include <QCameraViewfinderSettings>
#include "CameraImage.h"

typedef struct MediaInfo {
    int width;
    int height;
    double fps;
    QVideoFrame::PixelFormat format;
} MediaInfo;

// 头文件
class CnmernSelThread : public QObject
{
    Q_OBJECT
private:
    // params
    QCameraInfo m_selcaminfo;
    MediaInfo m_mediaInfo;
    // obj
    QCamera *m_cameraSelect = nullptr;
    CameraImage *m_image = nullptr;

public:
    CnmernSelThread(QObject* parent = nullptr);
    ~CnmernSelThread();

    void setInput(QCameraInfo selcaminfo, MediaInfo mediaInfo);

public slots:
    void start1();
    void doWork();
    // callback
    void recvCaptureFrame(const QVideoFrame & frame);

signals:
    void workFinished(int param1);
    void workStart();

    // send sign
    void getFrameByThread(const QVideoFrame & frame);
};


#endif
