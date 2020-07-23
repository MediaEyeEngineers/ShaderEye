#ifndef	SHADER_EYE_CUSTOM_COMPONENT_H
#define	SHADER_EYE_CUSTOM_COMPONENT_H

#include "EyerGL/EyerGL.hpp"
#include "EyerCore/EyerCore.hpp"

class ShaderEyeBGRACamera : public Eyer::EyerGLComponent
{
public:
    ShaderEyeBGRACamera(EyerGLContext * _ctx);
    ~ShaderEyeBGRACamera();

    int SetTexture(Eyer::EyerGLTexture * _frameTexture);

    virtual int Draw();

private:
    EyerGLContext * ctx = nullptr;

    Eyer::EyerGLDraw * bgra = nullptr;
    Eyer::EyerGLVAO * vao = nullptr;

    Eyer::EyerGLTexture * frameTexture = nullptr;
};


#endif
