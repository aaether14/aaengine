#ifndef FBXRENDERER_H
#define FBXRENDERER_H



#include <renderer/baserenderer.hpp>
#include <fbx_manager/mesh.hpp>




class FbxRenderer : public BaseRenderer
{


public:


    FbxRenderer();



    void Render(QObject *parent);



};

#endif // FBXRENDERER_H
