#include <fbx_manager/fbxmanager.hpp>




FBXManager::FBXManager(QObject *parent) : QObject(parent)
{


    setObjectName("FBXManager");




}




void FBXManager::LoadFromFBX(const char* fileName)
{


    FbxManager* manager = FbxManager::Create();
    FbxIOSettings* ioSettings = FbxIOSettings::Create(manager, IOSROOT);
    manager->SetIOSettings(ioSettings);
    FbxImporter* importer = FbxImporter::Create(manager, "");
    bool initialised = importer->Initialize(fileName, -1, manager->GetIOSettings());
    if(!initialised)
    {
        qDebug() << "Failed importer";
        return;
    }


    mScene = FbxScene::Create(manager, "default_scene");
    importer->Import(mScene);
    importer->Destroy();





    FbxNode * rootNode = mScene->GetRootNode();



    for (int i = 0; i < rootNode->GetChildCount(); i++)
    {



          FbxNode * current_node = rootNode->GetChild(i);
          if(current_node->GetNodeAttribute() == NULL)
             continue;

          FbxNodeAttribute::EType AttributeType = current_node->GetNodeAttribute()->GetAttributeType();

          if(AttributeType != FbxNodeAttribute::eMesh)
             continue;



          FbxMesh * mesh = current_node->GetMesh();







    }





}






