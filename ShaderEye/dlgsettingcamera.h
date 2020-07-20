#ifndef DLGSETTINGCAMERA_H
#define DLGSETTINGCAMERA_H

#include <QDialog>
#include <QCamera>

#include <QList>
#include <QCameraViewfinderSettings>
class CameraImage;
namespace Ui {
class DlgSettingCamera;
}

typedef struct MediaInfo {
    int width;
    int height;
    double fps;
    QVideoFrame::PixelFormat format;
} MediaInfo;

class DlgSettingCamera : public QDialog
{
    Q_OBJECT

public:
    explicit DlgSettingCamera(QWidget *parent = 0);
    ~DlgSettingCamera();
    const MediaInfo setMediaInfo(int w, int h, int fps, QVideoFrame::PixelFormat format);
    const MediaInfo getMediaInfo();

private slots:
    // btn click event
    void cameraListClick();
    // callback
    void recvCaptureFrame(const QVideoFrame & frame);

signals:
    void readFrame(const uchar *data, qint64 startTime);

private:
    Ui::DlgSettingCamera *ui;
    QCamera *m_selectedcamera = nullptr;
    CameraImage *m_image = nullptr;
    QList<QCameraInfo> m_cameras;
    MediaInfo m_mediaInfo;

    uchar *m_frameData = nullptr;

};

#endif // DLGSETTINGCAMERA_H
