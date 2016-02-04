#ifndef FBXMANAGER_H
#define FBXMANAGER_H



#include <QObject>
#include <QDebug>
#include <QSharedPointer>
#include <fbx_manager/meshentry.hpp>




class FBXManager : public QObject
{



    Q_OBJECT
    FbxManager * manager;
    QVector<QSharedPointer<MeshEntry> > mesh_entries;



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
