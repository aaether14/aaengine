#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP




#include <QMainWindow>
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


    explicit Controller(QWidget *parent = 0);
    ~Controller();



private slots:



    void on_actionConsole_triggered();
    void on_actionAbout_triggered();



    void ResetScriptEngine();



private:
    Ui::Controller *ui;



};







#endif // CONTROLLER_HPP
