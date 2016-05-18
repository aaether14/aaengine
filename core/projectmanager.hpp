#ifndef PROJECTMANAGER_H
#define PROJECTMANAGER_H




#include <QSemaphore>
#include <QWidget>
#include <QDir>



#include <utils/math.hpp>
#include <core/gl/fps.hpp>
#include <core/globalsettings.hpp>
#include <core/gl/inputregister.hpp>
#include <script_module/scriptengine.hpp>
#include <assets/assetloader.hpp>





/**
 *@brief The ProjectManager class will handle the loading of Aaether Engine's
 *projects
 */
class ProjectManager : public QObject
{


    Q_OBJECT


    /**
     *@brief m_loaded_sempahore knows whether or not a project has been loaded
     */
    QSemaphore m_loaded_semaphore;



public:



    /**
     * @brief ProjectManager will load the project pointed by config.json
     * @param parent is the parent of the QObject
     */
    explicit ProjectManager(QObject *parent = 0);



    /**
     * @brief SetProjectLoaded will set if a project has been loaded
     * @param project_loaded is whether or not the project is loaded
     */
    inline void SetProjectLoaded(const bool &project_loaded){
        if (project_loaded)
            m_loaded_semaphore.release();
        else
            m_loaded_semaphore.acquire(qMin(1, m_loaded_semaphore.available()));
    }



    /**
     * @brief GetProjectLoaded returns if a project has been loaded
     * @return true if the project has been loaded
     */
    inline bool GetProjectLoaded() const{
        return m_loaded_semaphore.available();
    }



    /**
     *@brief LoadProjectAndModifyConfig will, aside from loading the project
     *from config json, modify the config json with the new path of the project
     *@param project_path is the path of the project to be loaded
     */
    void LoadProjectAndModifyConfig(const QString &project_path);



signals:



    /**
     *@brief hasLoadedProject will send a signal upon project loading
     */
    void hasLoadedProject();




public slots:



    /**
     * @brief LoadProject will unload the currently loaded project and load a new one
     */
    virtual void LoadProject();



    /**
     *@brief UnloadProject will unload a project deleting the Settings object
     *in the ScriptEngine
     */
    virtual void UnloadProject();



};

#endif // PROJECTMANAGER_H
