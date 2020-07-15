#include "EyerGLCustomComponent.hpp"
#include "EyerType/EyerType.hpp"
#include "EyerGLShader/Shader.hpp"

#ifdef EYER_PLATFORM_WINDOWS
#include <windows.h>
#else
#include <locale.h>
#endif

namespace Eyer {
    EyerGLTextMeshDraw::EyerGLTextMeshDraw()
    {

    }

    EyerGLTextMeshDraw::~EyerGLTextMeshDraw()
    {

    }

    int EyerGLTextMeshDraw::Draw()
    {
        return 0;
    }
}
