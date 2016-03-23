#ifndef PROJECTMANAGER_H
#define PROJECTMANAGER_H




#include <QWidget>
#include <QShortcut>
#include <QDir>



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
     *@brief LoadProjectAndModifyConfig will, aside from loading the project
     *from config json, modify the config json with the new path
     *@param project_path is the path of the project to be loaded
     */
    void LoadProjectAndModifyConfig(QString project_path);



signals:


    /**
     * @brief resetScriptEngine - upon project reloading the script engine needs to be reset
     */
    void shouldResetScriptEngine();


    /**
     *@brief hasLoadedProject will send a signal upon project loading
     */
    void hasLoadedProject();




public slots:



    /**
     * @brief LoadProject will unload the currently loaded project and load a new one
     */
    void LoadProject();



    /**
     *@brief UnloadProject will unload a project deleting the Settings object
     *in the ScriptEngine
     */
    void UnloadProject();



};

#endif // PROJECTMANAGER_H
