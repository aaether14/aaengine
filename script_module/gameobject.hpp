#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H




#include <QObject>
#include <QMatrix4x4>




class GameObject : public QObject
{


    Q_OBJECT



    Q_PROPERTY(QMatrix4x4 g_viewProj READ getViewProj WRITE setViewProj)



    Q_PROPERTY(QVariant g_Components READ getComponents WRITE setComponents)



    /**
     *@brief g_viewProj will contain the view projection matrix of the current
     *camera
     */
    QMatrix4x4 g_viewProj;




    /**
     *@brief g_Components will contain the components of the scene
     */
    QVariant g_Components;




public:


    explicit GameObject(QObject *parent = 0);



    /**
     * @brief getViewProj is a getter to access g_viewProj
     * @return
     */
    inline QMatrix4x4 getViewProj(){return g_viewProj; }


    /**
     * @brief setViewProj is a setter to modify g_viewProj
     * @param view_proj
     */
    inline void setViewProj(QMatrix4x4 view_proj){g_viewProj = view_proj; }



    /**
     * @brief getComponents is a getter to access g_Components
     * @return
     */
    inline QVariant getComponents(){return g_Components; }


    /**
     * @brief setComponents is a setter to modify g_Components
     * @param components
     */
    inline void setComponents(QVariant components){g_Components = components; }


signals:




public slots:


};

#endif // GAMEOBJECT_H
