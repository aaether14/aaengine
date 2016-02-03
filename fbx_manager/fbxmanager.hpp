#ifndef FBXMANAGER_H
#define FBXMANAGER_H



#include <QObject>
#include <QDebug>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions>
#include <fbxsdk.h>




class FBXManager : public QObject
{


    Q_OBJECT


    FbxManager * manager;
    QOpenGLVertexArrayObject vao;
    QOpenGLBuffer vbo;
    QOpenGLBuffer ibo;


    int tri_count;



public:



    explicit FBXManager(QObject *parent = 0);
    ~FBXManager();



    void LoadFromFBX(const char * file_name, QOpenGLShaderProgram & shader);
    void Draw(QOpenGLFunctions * f);
    /**
    FBX manager
    */
    inline FbxManager * GetManager(){return manager; }



signals:




public slots:
};

#endif // FBXMANAGER_H
