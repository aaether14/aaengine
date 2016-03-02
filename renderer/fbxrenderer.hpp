#ifndef FBXRENDERER_H
#define FBXRENDERER_H



#include <renderer/baserenderer.hpp>
#include <assets/assetloader.hpp>
#include <script_module/scriptengine.hpp>




/**
 * @brief The FbxRenderer handles the rendering of Fbx meshes
 */
class FbxRenderer : public BaseRenderer
{



    /**
     * @brief The light struct will hold basic light data to be sent to shader
     */
    struct light
    {
        QVector4D ambient_color;
        QVector4D diffuse_color;
        QVector4D position;
        QVector4D type_data;
    };




    /**
     * @brief HandleLights takes light components and sends them trough ssbo to fragment shader
     * @param light_map - the part of components library pointing to lights in scene
     */
    void HandleLights(QVariantMap light_map);



    /**
     * @brief light_ssbo is a shader storage buffer object which is used to send scene light data to fragment shader
     */
    GLuint light_ssbo;




public:


    /**
     * @brief FbxRenderer will load the basic fbx render shader and also will create the light_ssbo
     */
    FbxRenderer();
    /**
      @brief ~FbxRenderer will reimplement the BaseRenderer destructor in order to also delete the ligth ssbo
    */
    ~FbxRenderer();


    /**
     * @brief Render will render the mesh components taking in account also the transform components
     * @param parent is needed to acces the Settings object which stores the mesh components
     * @return
     */
    bool Render(QObject *parent);



};

#endif // FBXRENDERER_H
