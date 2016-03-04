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
    fbx_shader->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/fbx_render.vert");
    fbx_shader->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/fbx_render.frag");
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



bool FbxRenderer::Render(QObject *parent)
{




    if (!parent->findChild<QObject*>("GL")->findChild<AssetLoader*>("AssetLoader"))
    {
        qDebug() << "Could not find Asset Loader!";
        return false;
    }
    if(!parent->findChild<ScriptEngine*>("ScriptEngine"))
    {
        qDebug() << "Could not find Script Engine!";
        return false;
    }




    AssetLoader * al = parent->findChild<QObject*>("GL")->findChild<AssetLoader*>("AssetLoader");
    ScriptEngine * se = parent->findChild<ScriptEngine*>("ScriptEngine");




    if (!se->findChild<QObject*>("Settings"))
    {
        qDebug() << "Could not find Settings object inside Script Engine!";
        return false;
    }





    GetShader("Fbx")->bind();
    QObject * scene = se->findChild<QObject*>("Settings");






    QVariant out_viewProj;
    if (QMetaObject::invokeMethod(scene,
                                  "getCamera",
                                  Q_RETURN_ARG(QVariant, out_viewProj)))
    {


        GetShader("Fbx")->setUniformValue("VP", out_viewProj.value<QMatrix4x4>());


    }
    else
    {
        qDebug() << "Could not call getCamera method in the Settings object!";
        return false;
    }






    QVariant scene_components;
    if (QMetaObject::invokeMethod(scene,
                                  "getComponents",
                                  Q_RETURN_ARG(QVariant, scene_components)))
    {




        QVariantMap components = scene_components.toMap();
        if (components.isEmpty())
            return true;



        HandleLights(components["Light"].toMap());



        foreach(auto it, components["Mesh"].toMap())
        {



            QVariantMap mesh_component = it.toMap();
            QString asset_name = mesh_component["asset"].toString();



            if (!al->HasAsset(asset_name))
            {
                qDebug() << "Could not find " << asset_name << " inside the asset library!";
                continue;
            }



            if (!dynamic_cast<MeshAsset*>(al->GetAsset(asset_name)))
            {
                qDebug() << "Asset is not mesh!";
                continue;
            }




            Mesh * current_mesh_component = static_cast<MeshAsset*>(al->GetAsset(asset_name))->GetMesh();
            QMatrix4x4 transform = components["Transform"].toMap()[mesh_component["transform"].toString()].toMap()["model"].value<QMatrix4x4>();





            QString draw_method = mesh_component["draw_method"].toString();
            if (draw_method.size())
                current_mesh_component->SetDrawMethod(draw_method);




            current_mesh_component->SetGlobalTransform(transform);
            current_mesh_component->Draw(*GetShader("Fbx"));



        }


    }
    else
    {
        qDebug() << "Could not call getComponents method in the Settings object!";
        return false;
    }




    GetShader("Fbx")->release();



    return true;



}



