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
     *@brief ResetScriptEngine will delete and reinitialize ScriptEngine
     */
    void ResetScriptEngine();



private:
    Ui::Controller *ui;



};







#endif // CONTROLLER_HPP
