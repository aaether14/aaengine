#ifndef FBXRENDERER_H
#define FBXRENDERER_H



#include <renderer/baserenderer.hpp>
#include <assets/assetloader.hpp>
#include <script_module/scriptengine.hpp>




class FbxRenderer : public BaseRenderer
{


public:


    FbxRenderer();


    bool Render(QObject *parent);



};

#endif // FBXRENDERER_H
