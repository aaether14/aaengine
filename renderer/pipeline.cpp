#include <renderer/pipeline.hpp>





void Pipeline::AddRenderer(const QString &renderer_name,
                           BaseRenderer *renderer)
{


    /**
    *Insert the provided renderer in the hash
    */
    renderers.insert(renderer_name, renderer);


}



Pipeline::Pipeline(QObject *parent) : QObject(parent)
{



    /**
     *First the name of the QObject
     */
    setObjectName("Pipeline");


    /**
     *Add the renderers used by the engine
     */
    AddRenderer("FbxRenderer", new FbxRenderer());




}







void Pipeline::Render()
{



    /**
     *We first need the main controller
     */
    QObject * main_controller = parent()->parent()->parent();



    /**
    *We then need project manager to acces the project we try to render
    */
    if (!main_controller->findChild<ProjectManager*>("ProjectManager"))
    {
        qDebug() << "Pipeline: Could not find ProjectManager!";
        return;
    }


    /**
    *We also need asset manager in order to access assets and perform sanity
    *check on them
    */
    if (!main_controller->findChild<AssetLoader*>("AssetLoader"))
    {
        qDebug() << "Pipeline: Could not find AssetLoader!";
        return;
    }


    /**
     *Get the project manager
     */
    ProjectManager * project_manager = main_controller->findChild<ProjectManager*>("ProjectManager");


    /**
    *Get the asset loader
    */
    AssetLoader * asset_loader = main_controller->findChild<AssetLoader*>("AssetLoader");



    /**
    *If the project has not been successfully loaded there's no point in try to
    *render anything
    */
    if (!project_manager->GetProjectLoaded())
        return;



    /**
    *Loop through the renderers and let them do their job
    */
    foreach(auto it, renderers.keys())
    {



        try
        {

            /**
            *Try to activate renderers
            */
            renderers[it]->Render(main_controller);


        }
        catch(aae::AError &error)
        {


            /**
            *Catch any error and output the issue
            */
            qDebug() << "Pipeline: " << it << " failed!";
            qDebug() << error.what();



            /**
            *If the meshes have been loaded it's safe to unload the project
            *that has unmet dependencies (missing assets)
            */
            if (asset_loader->SanityCheck())
            {
                qDebug() << "There are some entities that require assets that have not been loaded! Unloading project...";
                project_manager->UnloadProject();
            }



        }



    }



}





Pipeline::~Pipeline()
{


    /**
     *Delete the renderers
     */
    qDeleteAll(renderers);
    renderers.clear();



}



