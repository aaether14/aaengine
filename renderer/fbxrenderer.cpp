#include <renderer/fbxrenderer.hpp>




FbxRenderer::FbxRenderer()
{




    QOpenGLShaderProgram * fbx_shader = new QOpenGLShaderProgram();
    fbx_shader->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/fbx_render.vert");
    fbx_shader->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/fbx_render.frag");
    fbx_shader->link();



    AddShader("Fbx", fbx_shader);



}



void FbxRenderer::Render(QObject *parent)
{




    if (!parent->findChild<QObject*>("GL")->findChild<AssetLoader*>("AssetLoader") ||
            !parent->findChild<ScriptEngine*>("ScriptEngine"))
        return;



    GetShader("Fbx")->bind();




    AssetLoader * al = parent->findChild<QObject*>("GL")->findChild<AssetLoader*>("AssetLoader");
    ScriptEngine * se = parent->findChild<ScriptEngine*>("ScriptEngine");




    if (se->findChild<QObject*>("Settings"))
    {




        QObject * scene = se->findChild<QObject*>("Settings");
        if (scene->property("out_viewProj").isValid())
        {
            GetShader("Fbx")->setUniformValue("VP",
                                              qvariant_cast<QMatrix4x4>(scene->property("out_viewProj")));
        }






        if (scene->property("out_components").isValid())
        {

            QVariantMap components = qvariant_cast<QVariantMap>(scene->property("out_components"));
            for (auto it : qvariant_cast<QVariantMap>(components["Mesh"]))
            {



                QVariantMap mesh_component = qvariant_cast<QVariantMap>(it);
                Mesh * current_mesh_component = static_cast<MeshAsset*>(al->GetAsset(qvariant_cast<QString>(mesh_component["asset"])))->GetMesh();



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


    }






    GetShader("Fbx")->release();



}



