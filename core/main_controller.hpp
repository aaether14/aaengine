#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP




#include <QMainWindow>



#include <core/glcontroller.hpp>
#include <dialogs/console/console.hpp>
#include <dialogs/about/about.hpp>
#include <dialogs/mesh_import_dialog/meshimport.hpp>
#include <core/projectmanager.hpp>
#include <utils/math.hpp>





namespace Ui {
class Controller;
}





/**
 *@brief The Controller class is the main instance of the AaetherEngine, it
 *will manange other subinstances of the engine and also manage events from
 *QActions in the UI
 */
class Controller : public QMainWindow
{



    Q_OBJECT





public:


    /**
     * @brief Controller will initialize the project mananger and the script engine
     * @param parent
     */
    explicit Controller(QWidget *parent = 0);
    /**
    *@brief ~Controller - basic destructor
    */
    ~Controller();



private slots:


    /**
     *@brief on_actionConsole_triggered will determine what happens when
     *console action is triggered
     */
    void on_actionConsole_triggered();
    /**
     *@brief on_actionAbout_triggered will determine what happens when about
     *action is triggered
     */
    void on_actionAbout_triggered();
    /**
     *@brief on_actionProject_triggered will determine what happens when
     *project action is triggered
     */
    void on_actionProject_triggered();
    /**
     *@brief on_actionExit_triggered will determine what happens when exit
     *action is triggered
     */
    void on_actionExit_triggered();
    /**
     *@brief on_actionRebuild_triggered will determine what happens when
     *rebuild action is triggered
     */
    void on_actionRebuild_triggered();
    /**
    * @brief on_actionPlay_toggled will toggle whether the game is playing or not
    * @param arg1 is the value of play action (checkable)
    */
    void on_actionPlay_toggled(bool arg1);

    /**
     *@brief on_actionImport_triggered will determine what happens when import
     *action is triggered
     */
    void on_actionImport_triggered();


    /**
     *@brief ResetScriptEngine will delete and reinitialize ScriptEngine
     */
    void ResetScriptEngine();



private:
    Ui::Controller *ui;



};







#endif // CONTROLLER_HPP
