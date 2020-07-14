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

class DlgSettingCamera : public QDialog
{
    Q_OBJECT

public:
    explicit DlgSettingCamera(QWidget *parent = 0);
    ~DlgSettingCamera();

private slots:
    void btn_getcamera_list();
    void btn_pbtn_startcapture_clicked();
    void on_capture_frame(const QVideoFrame & frame );
private:
    Ui::DlgSettingCamera *ui;
    QCamera *m_selectedcamera;
    CameraImage * image;
    QList<QCameraViewfinderSettings> settinglist;
};

#endif // DLGSETTINGCAMERA_H
