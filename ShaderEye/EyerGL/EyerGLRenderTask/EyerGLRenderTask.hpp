#ifndef	EYER_LIB_GL_RENDER_TASK_H
#define	EYER_LIB_GL_RENDER_TASK_H

#include "EyerCore/EyerCore.hpp"
#include "EyerGL/EyerGLCustomComponent/EyerGLCustomComponent.hpp"

namespace Eyer
{
    class EyerGLRenderTask
    {
    public:
        EyerGLRenderTask();
        virtual ~EyerGLRenderTask();

        int SetWH(int w, int h);

        // 外部只能复写，不能调用
        virtual int Render() = 0;
        virtual int Init() = 0;
        virtual int Destory() = 0;

    public:
        int w = 0;
        int h = 0;
    };

    class EyerGLRenderTaskQueue
    {
    public:
        EyerGLRenderTaskQueue();
        ~EyerGLRenderTaskQueue();

        int GetSize();

        int PushRendTask(EyerGLRenderTask * renderTask);
        int PopAndRender(int w, int h);
        int PopAndRenderAndFree(int w, int h);

        int PopAndFree();
    private:
        EyerLockQueue<EyerGLRenderTask> taskQueue;
    };


    class JuliaRenderTask : public EyerGLRenderTask
    {
    public:
        JuliaRenderTask();
        ~JuliaRenderTask();

        virtual int Render();
        virtual int Init();
        virtual int Destory();

    private:
        EyerGLJulia * julia = nullptr;
    };


    class YUVRenderTask : public EyerGLRenderTask
    {
    public:
        YUVRenderTask();
        ~YUVRenderTask();

        virtual int Render();
        virtual int Init();
        virtual int Destory();

        int SetY(unsigned char * y, int w, int h);
        int SetU(unsigned char * u, int w, int h);
        int SetV(unsigned char * v, int w, int h);
    private:
        EyerGLYUV2TextureComponent * yuv2text = nullptr;
        EyerGLTexture * yTex = nullptr;
        EyerGLTexture * uTex = nullptr;
        EyerGLTexture * vTex = nullptr;

        int yW = 0;
        int yH = 0;
        unsigned char * yData = nullptr;

        int uW = 0;
        int uH = 0;
        unsigned char * uData = nullptr;

        int vW = 0;
        int vH = 0;
        unsigned char * vData = nullptr;
    };
}


#endif