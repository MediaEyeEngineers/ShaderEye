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


class ShaderEyeRender : public Eyer::EyerGLComponent
{
public:
    ShaderEyeRender(EyerGLContext * _ctx);
    ~ShaderEyeRender();

    int SetCameraTexture(Eyer::EyerGLTexture * _cameraTexture);

    int SetShader(const char * vertex, const char * fragment, Eyer::EyerGLShaderError & vertexShaderError, Eyer::EyerGLShaderError & fragmentShaderError, Eyer::EyerGLProgramError & programError);

    virtual int Draw();
private:
    EyerGLContext * ctx = nullptr;
    Eyer::EyerGLTexture * cameraTexture = nullptr;

    Eyer::EyerGLDraw * draw = nullptr;
    Eyer::EyerGLVAO * vao = nullptr;
};


#endif
