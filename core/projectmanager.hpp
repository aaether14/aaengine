#ifndef PROJECTMANAGER_H
#define PROJECTMANAGER_H




#include <QWidget>
#include <QShortcut>
#include <utils/json.hpp>
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
     *@brief is_project_loaded holds whether or not a project has been loaded
     */
    bool is_project_loaded;


    /**
     *@brief config_json will hold the information specified in the config.json
     */
    QJsonDocument config_json;



public:


    /**
     * @brief ProjectManager - it will load the project pointed by config.json
     * @param parent
     */
    explicit ProjectManager(QObject *parent = 0);


    /**
     * @brief SetProjectLoaded will set if a project has been loaded
     * @param project_loaded
     */
    inline void SetProjectLoaded(bool project_loaded){is_project_loaded = project_loaded; }
    /**
     * @brief GetProjectLoaded returns is a project has been loaded
     * @return
     */
    inline bool GetProjectLoaded(){return is_project_loaded; }



    /**
     * @brief LoadProject will unload the currently loaded project and load a new one
     * @param project_name is the name of the project to be loaded
     */
    void LoadProject(QString project_name);
    /**
     *@brief UnloadProject will unload a project deleting the Settings object
     *in the ScriptEngine
     */
    void UnloadProject();



signals:



public slots:
};

#endif // PROJECTMANAGER_H
