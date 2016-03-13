#ifndef BASERENDERER_H
#define BASERENDERER_H



#include <QOpenGLShaderProgram>
#include <QHash>
#include <QString>
#include <QDebug>
#include <QObject>





class BaseRenderer
{



    /**
     * @brief shaders stores the shaders used by the renderer
     */
    QHash<QString, QOpenGLShaderProgram*> shaders;




public:



    /**
     * @brief BaseRenderer
     */
    BaseRenderer();
    /**
     * @brief ~BaseRenderer is set to virtual for abstractization reasons, will delete the shaders from the shader hash
     */
    virtual ~BaseRenderer();


    /**
     * @brief Render will be used by the renderer to activate its shaders
     * @param parent will be needed for acceses data in the engine
     */
    virtual void Render(QObject * parent) = 0;


protected:


    /**
     * @brief AddShader will add a shader to the shader hash
     * @param shader_name is a key for the shader to be added
     * @param shader will be initialized before being added to the library
     */
    virtual void AddShader(QString shader_name, QOpenGLShaderProgram *shader);


    /**
     * @brief GetShader will allow the deriving classes to acces the shaders stored privately in the base class,
     * could be reimplemented
     * @param shader_name is the key under which the shader is stored
     * @return
     */
    virtual QOpenGLShaderProgram * GetShader(QString shader_name);


};

#endif // BASERENDERER_H
