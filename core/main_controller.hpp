#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP




#include <QMainWindow>




#include <core/gl/glcontroller.hpp>
#include <dialogs/console/console.hpp>
#include <dialogs/about/about.hpp>
#include <dialogs/mesh_import_dialog/meshimport.hpp>
#include <core/projectmanager.hpp>





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
     *@brief Controller will initialize the project mananger and the script engine
     *@param parent is the parent of the QObject
     */
    explicit Controller(QWidget *parent = 0);
    /**
    *@brief ~Controller is a basic QWidget destructor
    */
    ~Controller();



private slots:



    /**
     *@brief TogglePlayOnProjectLoad will make sure whenever you load a project
     *the engine is not paused
     */
    void TogglePlayOnProjectLoad();



    /**
     *@brief on_actionProject_triggered will determine what happens when
     *project action is triggered
     */
    void on_actionProject_triggered();




private:



    /**
     *@brief closeEvent will reimplement the close event to make sure all
     *working threads have finished their work before closing the application
     */
    void closeEvent(QCloseEvent * event);



    /**
     * @brief ui is the ui layout of the main window
     */
    Ui::Controller *ui;



};







#endif // CONTROLLER_HPP
