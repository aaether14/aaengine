#include <fbx_manager/fbxmanager.hpp>




FBXManager::FBXManager(QObject *parent) : QObject(parent),
    ibo(QOpenGLBuffer::IndexBuffer), vbo(QOpenGLBuffer::VertexBuffer)
{


    setObjectName("FBXManager");


    manager = FbxManager::Create();
    FbxIOSettings* io_settings = FbxIOSettings::Create(manager, IOSROOT);
    manager->SetIOSettings(io_settings);




}




FBXManager::~FBXManager()
{

    manager->Destroy();

}






void FBXManager::LoadFromFBX(const char* file_name, QOpenGLShaderProgram & shader)
{





    FbxImporter* importer = FbxImporter::Create(GetManager(), "");
    bool initialised = importer->Initialize(file_name, -1, GetManager()->GetIOSettings());
    if(!initialised)
    {
        qDebug() << "Failed importer: " << file_name;
        return;
    }



    FbxScene * scene = FbxScene::Create(GetManager(), "default_scene");
    importer->Import(scene);
    importer->Destroy();






    FbxNode * rootNode = scene->GetRootNode();
    for (int i = 0; i < rootNode->GetChildCount(); i++)
    {



        FbxNode * current_node = rootNode->GetChild(i);
        if(!current_node->GetNodeAttribute())
            continue;

        FbxNodeAttribute::EType AttributeType = current_node->GetNodeAttribute()->GetAttributeType();

        if(AttributeType != FbxNodeAttribute::eMesh)
            continue;





        FbxMesh * mesh = current_node->GetMesh();





        QVector<unsigned int> indices;
        for (int i = 0; i < mesh->GetPolygonCount(); i++)
        {

            indices << (unsigned int)(mesh->GetPolygonVertex(i, 0));
            indices << (unsigned int)(mesh->GetPolygonVertex(i, 1));
            indices << (unsigned int)(mesh->GetPolygonVertex(i, 2));


        }
        tri_count = indices.size();






        QVector<float> vertices;
        for (int i = 0; i < mesh->GetControlPointsCount(); i++)
        {
            vertices << (float)(mesh->GetControlPointAt(i).mData[0]);
            vertices << (float)(mesh->GetControlPointAt(i).mData[1]);
            vertices << (float)(mesh->GetControlPointAt(i).mData[2]);
        }






        vao.create();
        vao.bind();



        shader.bind();
        vbo.create();
        vbo.setUsagePattern(QOpenGLBuffer::StaticDraw);
        vbo.bind();
        vbo.allocate(&vertices[0], sizeof(float) * vertices.size());


        shader.setAttributeBuffer("vertex", GL_FLOAT, 0, 3);
        shader.enableAttributeArray("vertex");



        ibo.create();
        ibo.setUsagePattern(QOpenGLBuffer::StaticDraw);
        ibo.bind();
        ibo.allocate(&indices[0], sizeof(unsigned int) * indices.size());





        vao.release();
        shader.release();




        indices.clear();
        vertices.clear();




    }





}



void FBXManager::Draw(QOpenGLFunctions *f)
{

    vao.bind();
    f->glDrawElements(GL_TRIANGLES, tri_count, GL_UNSIGNED_INT, 0);
    vao.release();

}






