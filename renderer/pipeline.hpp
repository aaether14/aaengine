#ifndef PIPELINE_H
#define PIPELINE_H




#include <QObject>
#include <QHash>
#include <QString>
#include <QOpenGLWidget>
#include <renderer/fbxrenderer.hpp>
#include <core/projectmanager.hpp>





class Pipeline : public QObject
{


    Q_OBJECT


    /**
     * @brief renderers stores in a hash all the renderers the engine needs
     */
    QHash<QString, BaseRenderer*> renderers;


    /**
     * @brief AddRenderer will add a renderer to the library
     * @param renderer_name is the key of new renderer
     * @param renderer is the initialized renderer to be added
     */
    void AddRenderer(const QString &renderer_name,
                     BaseRenderer* renderer);



public:


    /**
     * @brief Pipeline will add the engine's renderers
     * @param parent is part of default QObject constructor
     */
    explicit Pipeline(QObject *parent = 0);

    /**
    * @brief ~Pipeline will delete the renderers
    */
    ~Pipeline();



    /**
    * @brief Render will render the engines scene, could be reimplemented in a derived class
    */
    virtual void Render();




signals:



public slots:


};

#endif // PIPELINE_H
