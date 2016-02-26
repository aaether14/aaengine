#ifndef BASERENDERER_H
#define BASERENDERER_H



#include <QOpenGLShaderProgram>
#include <QHash>
#include <QString>
#include <QDebug>
#include <QObject>





class BaseRenderer
{



    QHash<QString, QOpenGLShaderProgram*> shaders;




public:



    BaseRenderer();
    ~BaseRenderer();



    virtual void Render(QObject * parent) = 0;


protected:


    virtual void AddShader(QString shader_name, QOpenGLShaderProgram *shader);


    virtual QOpenGLShaderProgram * GetShader(QString shader_name);


};

#endif // BASERENDERER_H
