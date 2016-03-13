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





    QObject * main_controller = parent()->parent()->parent();




    if (!main_controller->findChild<ProjectManager*>("ProjectManager"))
    {
        qDebug() << "Pipeline: Could not find ProjectManager!";
        return;
    }





    ProjectManager * pm = main_controller->findChild<ProjectManager*>("ProjectManager");



    if (!pm->GetProjectLoaded())
        return;




    foreach(auto it, renderers.keys())
    {




        try
        {


            renderers[it]->Render(main_controller);


        }
        catch(aae::AError &error)
        {



            qDebug() << "Pipeline: " << it << " failed!";
            qDebug() << error.what();



            pm->UnloadProject();



        }



    }



}





Pipeline::~Pipeline()
{


    qDeleteAll(renderers);
    renderers.clear();


}



