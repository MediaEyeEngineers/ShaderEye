QT       += core gui multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
TARGET = ShaderEye
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

DEFINES += QT_EYER_PLAYER

SOURCES += \
    CamerController.cpp \
    Util/CnmernSelThread.cpp \
    main.cpp \
    MainWindow.cpp \
    View/GLView.cpp \
    CameraImage.cpp

HEADERS += \
    CameraController.h \
    CommonSetting.h \
    MainWindow.h \
    Util/CnmernSelThread.h \
    View/GLView.hpp \
    CameraImage.h

FORMS += \
    CameraController.ui \
    MainWindow.ui


#### Eyer GL Shader
HEADERS += \
    EyerGLShader/Shader.hpp \
    EyerGLShader/ShaderH.hpp

SOURCES += \
    EyerGLShader/Shader.cpp

#### Eyer GL
HEADERS += \
    EyerGL/EyerGL.hpp \
    EyerGL/GLHeader.h \
    EyerGL/EyerGLCustomComponent/EyerGLCustomComponent.hpp

SOURCES += \
    EyerGL/EyerGLShader.cpp \
    EyerGL/EyerGLProgram.cpp \
    EyerGL/EyerGLTexture.cpp \
    EyerGL/EyerGLVAO.cpp \
    EyerGL/EyerGLFrameBuffer.cpp \
    EyerGL/EyerGLDraw.cpp \
    EyerGL/EyerGLComponent.cpp \
    EyerGL/EyerGLCustomComponent/EyerGLJulia.cpp

#### Eyer Core
HEADERS += \
    EyerCore/EyerCore.hpp \
    EyerCore/EyerLinkedEle.hpp \
    EyerCore/EyerLinkedList.hpp \
    EyerCore/EyerLockQueue.hpp \
    EyerCore/EyerLog.hpp \
    EyerCore/EyerLRUMap.hpp \
    EyerCore/EyerMap.hpp \
    EyerCore/EyerMapEle.hpp \
    EyerCore/EyerMath.hpp \
    EyerCore/EyerQueue.hpp \
    EyerCore/EyerString.hpp \
    EyerCore/EyerTime.hpp


SOURCES += \
    EyerCore/EyerLog.cpp \
    EyerCore/EyerMat.cpp \
    EyerCore/EyerMat2x1.cpp \
    EyerCore/EyerMat3x1.cpp \
    EyerCore/EyerMat4x1.cpp \
    EyerCore/EyerMat4x4.cpp \
    EyerCore/EyerRand.cpp \
    EyerCore/EyerString.cpp \
    EyerCore/EyerTime.cpp \
