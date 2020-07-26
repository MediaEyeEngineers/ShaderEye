#ifndef COMMONSETTING_H
#define COMMONSETTING_H

/**
 * @date 2020/07/20
 * @author changyanlong github.com/numberwolf q531365872
 */

#include <QVideoFrame>

#define STRING_VERSION                      "1.0.0"
#define STRING_ABOUT                        "关于 About"

/*
 * LOG_PLATFORM
 */
#ifdef Q_OS_WIN
#define     LOG_PLATFORM                    "Windows"
#elif defined(Q_OS_OSX)
#define     LOG_PLATFORM                    "MacOS"
#elif defined(Q_OS_LINUX)
#define     LOG_PLATFORM                    "Linux"
#endif


// TITLE
#define     TITLE_MAIN_WIN                  "ShaderEye - realrace.cn || github.com/MediaEyeEngineers"
#define     TITLE_CAMOPEN_WIN               "Camera Select"
#define     TITLE_COMPILE_LOG               "Compile Log"


/**
 * @brief CameraSetting
 */
const int CAM_WIDTH                         = 640;
const int CAM_HEIGHT                        = 480;
const int CAM_FPS                           = 20;
const QVideoFrame::PixelFormat CAM_FORMAT   = QVideoFrame::PixelFormat::Format_RGB24;

#endif // COMMONSETTING_H
