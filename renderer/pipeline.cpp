#include <renderer/pipeline.hpp>




void Pipeline::AddRenderer(QString renderer_name, BaseRenderer *renderer)
{


    renderers[renderer_name] = renderer;


}



Pipeline::Pipeline(QObject *parent) : QObject(parent)
{


    setObjectName("Pipeline");
    AddRenderer("FbxRenderer", new FbxRenderer());



}







void Pipeline::Render()
{


    for (auto it : renderers)
    {
        //Get main controller
        it->Render(parent()->parent()->parent());
    }


}





Pipeline::~Pipeline()
{


    qDeleteAll(renderers);


}



