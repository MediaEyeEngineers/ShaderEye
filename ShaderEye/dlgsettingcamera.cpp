#include "dlgsettingcamera.h"
#include "ui_dlgsettingcamera.h"
#include "cameraimage.h"
#include <QVideoFrame>
#include <QCameraInfo>

DlgSettingCamera::DlgSettingCamera(QWidget *parent) :
    m_selectedcamera(NULL),
    QDialog(parent),
    ui(new Ui::DlgSettingCamera)
{
    ui->setupUi(this);
    connect(ui->btn_GetCameraList,SIGNAL(clicked()),this,SLOT(btn_getcamera_list()));
    connect(ui->pbtn_startcapture,SIGNAL(clicked()),this,SLOT(btn_pbtn_startcapture_clicked()));
}

DlgSettingCamera::~DlgSettingCamera()
{
    delete ui;
}

QString PixformatToString(QVideoFrame::PixelFormat format)
{
    switch (format)
    {
    case QVideoFrame::Format_Invalid :
        return "Format_Invalid";
        break;
    case QVideoFrame::Format_ARGB32:
        return "Format_ARGB32";
        break;
    case QVideoFrame::Format_ARGB32_Premultiplied:
        return "Format_ARGB32_Premultiplied";
        break;
    case QVideoFrame::Format_RGB32:
        return "Format_RGB32";
        break;
    case QVideoFrame::Format_RGB24:
        return "Format_RGB24";
        break;
    case QVideoFrame::Format_RGB565:
        return "Format_RGB565";
        break;
    case QVideoFrame::Format_RGB555:
        return "Format_RGB555";
        break;
    case QVideoFrame::Format_ARGB8565_Premultiplied:
        return "Format_ARGB8565_Premultiplied";
        break;
    case QVideoFrame::Format_BGRA32:
        return "Format_BGRA32";
        break;
    case QVideoFrame::Format_BGRA32_Premultiplied:
        return "Format_BGRA32_Premultiplied";
        break;
    case QVideoFrame::Format_BGR32:
        return "Format_BGR32";
        break;
    case QVideoFrame::Format_BGR24:
        return "Format_BGR24";
        break;
    case QVideoFrame::Format_BGR565:
        return "Format_BGR565";
        break;
    case QVideoFrame::Format_BGR555:
        return "Format_BGR555";
        break;
    case QVideoFrame::Format_BGRA5658_Premultiplied:
        return "Format_BGRA5658_Premultiplied";
        break;

    case QVideoFrame::Format_AYUV444:
        return "Format_AYUV444";
        break;
    case QVideoFrame::Format_AYUV444_Premultiplied:
        return "Format_AYUV444_Premultiplied";
        break;
    case QVideoFrame::Format_YUV444:
        return "Format_YUV444";
        break;
    case QVideoFrame::Format_YUV420P:
        return "Format_YUV420P";
        break;
    case QVideoFrame::Format_YV12:
        return "Format_YV12";
        break;
    case QVideoFrame::Format_UYVY:
        return "Format_UYVY";
        break;
    case QVideoFrame::Format_YUYV:
        return "Format_YUYV";
        break;
    case QVideoFrame::Format_NV12:
        return "Format_NV12";
        break;
    case QVideoFrame::Format_NV21:
        return "Format_NV21";
        break;
    case QVideoFrame::Format_IMC1:
        return "Format_IMC1";
        break;
    case QVideoFrame::Format_IMC2:
        break;
    case QVideoFrame::Format_IMC3:
        return "Format_IMC3";
        break;
    case QVideoFrame::Format_IMC4:
        return "Format_IMC4";
        break;
    case QVideoFrame::Format_Y8:
        return "Format_Y8";
        break;
    case QVideoFrame::Format_Y16:
        return "Format_Y16";
        break;
    case QVideoFrame::Format_Jpeg:
        return "Format_Jpeg";
        break;

    case QVideoFrame::Format_CameraRaw:
        return "Format_CameraRaw";
        break;
    case QVideoFrame::Format_AdobeDng:
        return "Format_AdobeDng";
        break;
    case   QVideoFrame::NPixelFormats:
        return "NPixelFormats";
        break;
    default:
        break;
    }
}

void DlgSettingCamera::btn_getcamera_list()
{

    QList<QCameraInfo> cameras=QCameraInfo::availableCameras();   //获取所有可以支持的camera,包括Integrated camera和uvc camera
    foreach (const QCameraInfo &camerasInfo, cameras)
    {
        ui->comboBox_selcamera->addItem(camerasInfo.description());
        qDebug()<<"camera:"<<camerasInfo.description();
        qDebug()<<"name:"<<camerasInfo.deviceName();
        /*QCamera* mCamera=new QCamera(camerasInfo);  //由camerainfo创建qcamera
                       mCaptureVideoFrame=new CaptureVideoFrame(this);  //视频帧接收类,因为需要用自己写的opengl渲染,所以有了这个类,用来拿到相机的当前帧
                       connect(mCaptureVideoFrame,SIGNAL(CaptureFrame(QVideoFrame)),this,SLOT(on_captrueframecallback(QVideoFrame)));
                       mCaptureVideoFrame->setSource(mCamera);*/
    }
    ui->comboBox_selcamera->addItem("bbbbb");



    //取得选中的摄像头索引
    QCameraInfo m_camerainfo;

    QString sellcamera=ui->comboBox_selcamera->itemText(ui->comboBox_selcamera->currentIndex());
    foreach(const QCameraInfo &camerasInfo, cameras)
    {
        if(sellcamera==camerasInfo.description())//如果符合
        {
            m_camerainfo=camerasInfo;
            QCamera* camera=new QCamera(camerasInfo);
            camera->start();
            QList<QCameraViewfinderSettings > ViewSets = camera->supportedViewfinderSettings();
            settinglist=ViewSets;
           foreach (QCameraViewfinderSettings ViewSet, ViewSets)
                {
                    QString content;
                    content.append(QString::fromStdWString(L"最大帧率="));
                    content.append(QString::number(ViewSet.maximumFrameRate()));
                    content.append(QString::fromStdWString(L"最小帧率="));
                    content.append(QString::number(ViewSet.minimumFrameRate()));
                    content.append(QString::fromStdWString(L"分辨率="));


                    content.append(QString("(%1*%2)").arg(ViewSet.resolution().width()).arg(ViewSet.resolution().height()));
                    content.append(QString::fromStdWString(L"输出格式="));
                    content.append(PixformatToString(ViewSet.pixelFormat()));

                    ui->combobox_param->addItem(content);
                    qDebug() <<" max rate = " << ViewSet.maximumFrameRate() <<
                                "min rate = "<< ViewSet.minimumFrameRate() <<
                                QString::fromStdWString(L"分辨率=")<<
                                ViewSet.resolution()<<\
                                "Format="<<ViewSet.pixelFormat();
                }
            camera->stop();
            delete camera;
        }
    }

    QCameraInfo selcaminfo=cameras.at(ui->combobox_param->currentIndex());
    m_selectedcamera=new QCamera(selcaminfo);
    m_selectedcamera->setCaptureMode(QCamera::CaptureVideo);

}

void DlgSettingCamera::btn_pbtn_startcapture_clicked()
{
    QCameraViewfinderSettings ViewSet=settinglist.at(ui->combobox_param->currentIndex());
    qDebug()<<"frame rate"<< ViewSet.maximumFrameRate();
    qDebug()<<" pix format"<< ViewSet.pixelFormat();
    m_selectedcamera->setViewfinderSettings(ViewSet);

    image=new CameraImage(this);
    image->setSource(m_selectedcamera);
    connect(image,SIGNAL(CaptureFrame(const QVideoFrame&)),
            this,SLOT(on_capture_frame(const QVideoFrame &)));
    m_selectedcamera->start();
}

void DlgSettingCamera::on_capture_frame(const QVideoFrame &_frame)
{
        qDebug()<<_frame.pixelFormat();
}
