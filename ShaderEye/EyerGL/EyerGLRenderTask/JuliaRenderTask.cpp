#include "EyerGLRenderTask.hpp"
#include "EyerGLCustomComponent/EyerGLCustomComponent.hpp"

namespace Eyer
{
    JuliaRenderTask::JuliaRenderTask()
    {

    }

    JuliaRenderTask::~JuliaRenderTask()
    {

    }

    int JuliaRenderTask::Render()
    {
        julia->SetWH(w, h);
        julia->Draw();
        return 0;
    }

    int JuliaRenderTask::Init()
    {
        if(julia == nullptr){
            julia = new EyerGLJulia();
        }
        return 0;
    }

    int JuliaRenderTask::Destory()
    {
        if(julia == nullptr){
            delete julia;
            julia = nullptr;
        }
        return 0;
    }
}