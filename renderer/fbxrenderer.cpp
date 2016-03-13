#include <renderer/fbxrenderer.hpp>




void FbxRenderer::HandleLights(QVariantMap light_map)
{


    QVector<light> scene_lights;



    foreach(auto it, light_map)
    {



        QVariantMap light_component = it.toMap();
        light new_light;



        new_light.ambient_color = light_component["ambient_color"].value<QVector3D>();
        new_light.diffuse_color = light_component["diffuse_color"].value<QVector3D>();
        new_light.position = light_component["position"].value<QVector3D>();
        new_light.type_data.setX(light_component["light_type"].toFloat());



        scene_lights << new_light;


    }



    QOpenGLFunctions_4_3_Core * f = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_4_3_Core>();
    f->glBindBuffer(GL_SHADER_STORAGE_BUFFER, light_ssbo);
    f->glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(light) * scene_lights.size(), &scene_lights[0], GL_STATIC_DRAW);
    f->glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, light_ssbo);



    scene_lights.clear();



}




FbxRenderer::FbxRenderer() : light_ssbo(0)
{




    QOpenGLShaderProgram * fbx_shader = new QOpenGLShaderProgram();
    fbx_shader->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/__data/shaders/fbx_render.vert");
    fbx_shader->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/__data/shaders/fbx_render.frag");
    fbx_shader->link();



    AddShader("Fbx", fbx_shader);




    QOpenGLFunctions_4_3_Core * f = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_4_3_Core>();
    f->glGenBuffers(1, &light_ssbo);






}



FbxRenderer::~FbxRenderer()
{



    QOpenGLFunctions_4_3_Core * f = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_4_3_Core>();
    if (light_ssbo)
        f->glDeleteBuffers(1, &light_ssbo);



}





void FbxRenderer::Render(QObject *parent)
{




    /**
    *Check if you can find AssetLoader
    */


    if (!parent->findChild<QObject*>("GL")->findChild<AssetLoader*>("AssetLoader"))
    {

        throw aae::AError("Could not find Asset Loader!");

    }



    /**
    *Check if you can find ScriptEngine
    */

    if(!parent->findChild<ScriptEngine*>("ScriptEngine"))
    {

        throw aae::AError("Could not find Script Engine!");

    }



    /**
     *If AssetLoader and ScriptEngine are in the right location, get a
     *reference to them
     */

    AssetLoader * al = parent->findChild<QObject*>("GL")->findChild<AssetLoader*>("AssetLoader");
    ScriptEngine * se = parent->findChild<ScriptEngine*>("ScriptEngine");



    /**
    *Check if the ScriptEngine has a GameObject
    */


    if (!se->findChild<GameObject*>("GameObject"))
    {

        throw aae::AError("Could not find GameObject inside Script Engine!");

    }




    /**
    *Bind the shader used to render fbx meshes
    */


    GetShader("Fbx")->bind();



    /**
     *If GameObject is in the right location, get a reference to it
     */

    GameObject * game_object = se->findChild<GameObject*>("GameObject");



    /**
    *Extract the MVP from the GameObject and send it to shader
    */

    GetShader("Fbx")->setUniformValue("VP", game_object->getViewProj());




    /**
     *Extract components from the gameobject;
     */

    QVariantMap components = game_object->getComponents().toMap();




    /**
    *If there are no components to render, return
    */


    if (components.isEmpty())
        return;



    /**
     *Extract light components and send them to shader
     */

    HandleLights(components["Light"].toMap());



    /**
    *Loop through the mesh components and try to render each one
    */

    foreach(auto it, components["Mesh"].toMap())
    {



        /**
         *First extract the variant map holding information about the
         *mesh
         */
        QVariantMap mesh_component = it.toMap();


        /**
         *Get the name of the asset used by the mesh
         */

        QString asset_name = mesh_component["asset"].toString();



        /**
        *Check if the asset requested is in the library
        */

        if (!al->HasAsset(asset_name))
        {

            QString msg =  "Could not find " + asset_name + " inside the asset library!";
            throw aae::AError(msg);

        }

        /**
        *Check if the asset requested is actaully a MeshAsset
        */

        if (!dynamic_cast<MeshAsset*>(al->GetAsset(asset_name)))
        {

            throw aae::AError("Asset is not a MeshAsset!");

        }



        /**
         * If everything went well, get a pointer to the mesh of the MeshAsset
         */

        Mesh * current_mesh_component = static_cast<MeshAsset*>(al->GetAsset(asset_name))->GetMesh();

        /**
         *Extract the model matrix indicated by the Transform used by the mesh
         */

        QMatrix4x4 transform = components["Transform"].toMap()[mesh_component["transform"].toString()].toMap()["model"].value<QMatrix4x4>();



        /**
         *Get which draw method the mesh should use
         */

        QString draw_method = mesh_component["draw_method"].toString();


        /**
        *If the draw method is valid then set it for the mesh in cause
        */

        if (draw_method.size())
            current_mesh_component->SetDrawMethod(draw_method);



        /**
        *At last, load model matrix to the mesh then render it using the fbx
        *render shader
        */


        current_mesh_component->SetGlobalTransform(transform);
        current_mesh_component->Draw(*GetShader("Fbx"));



    }




    GetShader("Fbx")->release();





    return;



}



