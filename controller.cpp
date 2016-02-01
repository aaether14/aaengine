#include <controller.hpp>
#include "ui_controller.h"





Controller::Controller(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Controller)
{



    ui->setupUi(this);



    ScriptEngine * script_engine = new ScriptEngine(this);
    Console * console = new Console(this);




}





Controller::~Controller()
{
    delete ui;
}




void Controller::on_actionConsole_triggered()
{


    if (findChild<Console*>("Console"))
    findChild<Console*>("Console")->show();



}
