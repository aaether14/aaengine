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


    foreach(auto it, renderers.keys())
    {


        //parnet()->parent()->parent() should get the main controller


        if (!renderers[it]->Render(parent()->parent()->parent()))
            qDebug() << it << " failed!";



    }



}





Pipeline::~Pipeline()
{


    qDeleteAll(renderers);


}



