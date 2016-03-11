#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP




#include <QMainWindow>
#include <QFileDialog>



#include <core/glcontroller.hpp>
#include <console/console.hpp>
#include <about/about.hpp>
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



    /**
     * @brief OpenFileDialog will open a file dialog and return the file you chose,
     * it will also pause the engine while the file dialog is opened and unpause after
     * that
     * @param file_dialog_name is the name of the file dialog
     * @param suffix_to_look_for is the suffix of the files the file dialog will look for
     * @return the name of the file you chose from the dialog
     */
    QString OpenFileDialog(QString file_dialog_name, QString suffix_to_look_for);




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
