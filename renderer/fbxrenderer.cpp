#include <renderer/fbxrenderer.hpp>




FbxRenderer::FbxRenderer()
{




    QOpenGLShaderProgram * fbx_shader = new QOpenGLShaderProgram();
    fbx_shader->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/fbx_render.vert");
    fbx_shader->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/fbx_render.frag");
    fbx_shader->link();



    AddShader("Fbx", fbx_shader);



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
    if (scene->property("out_viewProj").isValid())
    {
        GetShader("Fbx")->setUniformValue("VP",
                                          scene->property("out_viewProj").value<QMatrix4x4>());
    }
    else
    {
        qDebug() << "Could not extract out_viewProj from Settings object";
        return false;
    }






    if (scene->property("out_components").isValid())
    {



        QVariantMap components = scene->property("out_components").toMap();
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
        qDebug() << "Could not extract out_components from Settings object!";
        return false;
    }




    GetShader("Fbx")->release();



    return true;



}



