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
            Mesh * current_mesh_component = static_cast<MeshAsset*>(al->GetAsset(mesh_component["asset"].toString()))->GetMesh();



            QMatrix4x4 transform;
            QVariantMap transform_component = qvariant_cast<QVariantMap>((qvariant_cast<QVariantMap>(components["Transform"]))[
                    qvariant_cast<QString>(mesh_component["transform"])]);
            transform.translate(qvariant_cast<QVector3D>(transform_component["position"]));
            transform.scale(qvariant_cast<QVector3D>(transform_component["scale"]));
            transform.rotate(QQuaternion::fromEulerAngles(qvariant_cast<QVector3D>(transform_component["rotation"])));




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



