#include "EyerGLRenderTask.hpp"
#include "EyerGLCustomComponent/EyerGLCustomComponent.hpp"

namespace Eyer
{
    YUVRenderTask::YUVRenderTask()
    {

    }

    YUVRenderTask::~YUVRenderTask()
    {

    }

    int YUVRenderTask::Render()
    {
        if(yData != nullptr){
            yTex->SetDataRedChannel(yData, yW, yH);
        }

        if(uData != nullptr){
            uTex->SetDataRedChannel(uData, uW, uH);
        }

        if(vData != nullptr){
            vTex->SetDataRedChannel(vData, vW, vH);
        }
        
        yuv2text->SetYTexture(yTex);
        yuv2text->SetUTexture(uTex);
        yuv2text->SetVTexture(vTex);

        yuv2text->SetColoRange(EyerGLYUV2TextureComponentColorRange::COLOR_RANGE_JPEG);

        yuv2text->Draw();

        // free(yyy);
        return 0;
    }

    int YUVRenderTask::Init()
    {
        if(yuv2text == nullptr){
            yuv2text = new EyerGLYUV2TextureComponent();

            yTex = new EyerGLTexture();
            uTex = new EyerGLTexture();
            vTex = new EyerGLTexture();

            yuv2text->SetYTexture(yTex);
            yuv2text->SetUTexture(uTex);
            yuv2text->SetVTexture(vTex);

            yuv2text->SetColoRange(EyerGLYUV2TextureComponentColorRange::COLOR_RANGE_JPEG);
        }

        return 0;
    }

    int YUVRenderTask::Destory()
    {
        if(yuv2text == nullptr){
            delete yuv2text;
            yuv2text = nullptr;
        }
        if(yTex == nullptr){
            delete yTex;
            yTex = nullptr;
        }
        if(uTex == nullptr){
            delete uTex;
            uTex = nullptr;
        }
        if(vTex == nullptr){
            delete vTex;
            vTex = nullptr;
        }

        if(yData != nullptr){
            free(yData);
            yData = nullptr;
        }
        if(uData != nullptr){
            free(uData);
            uData = nullptr;
        }
        if(vData != nullptr){
            free(vData);
            vData = nullptr;
        }

        return 0;
    }

    int YUVRenderTask::SetY(unsigned char * y, int w, int h)
    {
        if(yData != nullptr){
            free(yData);
            yData = nullptr;
        }
        yData = (unsigned char *)malloc(w * h);

        yW = w;
        yH = h;
        
        memcpy(yData, y, w * h);

        return 0;
    }

    int YUVRenderTask::SetU(unsigned char * u, int w, int h)
    {
        if(uData != nullptr){
            free(uData);
            uData = nullptr;
        }
        uData = (unsigned char *)malloc(w * h);

        uW = w;
        uH = h;
        
        memcpy(uData, u, w * h);

        return 0;
    }

    int YUVRenderTask::SetV(unsigned char * v, int w, int h)
    {
        if(vData != nullptr){
            free(vData);
            vData = nullptr;
        }
        vData = (unsigned char *)malloc(w * h);

        vW = w;
        vH = h;
        
        memcpy(vData, v, w * h);
        
        return 0;
    }
}
