#include <dialogs/console/console.hpp>
#include "ui_console.h"






Console::Console(QWidget *parent) :
    baseDialog(parent),
    ui(new Ui::Console)
{




    ui->setupUi(this);




    /**
    *Set the stretch factor for the splitter in the console and also the color
    *of the text
    */
    ui->splitter->setStretchFactor(0, 2);
    ui->splitter->setStretchFactor(1, 1);
    ui->console_output->setTextColor(Qt::red);





#ifdef AAE_REDIRECT_MESSAGES_TO_INGAME_CONSOLE
    /**
    *Start redirecting the console output to in-game console
    */
    Logger::Instance()->SetConsoleOutputPointer(ui->console_output);
#endif






}




Console::~Console()
{


    /**
    *Just delete the ui
    */
    delete ui;


}





void Console::on_run_script_button_clicked()
{



    /**
    *If you can find the ScriptEngine go ahead and send the text written in the
    *console to it to be run
    */
    if (parent()->findChild<ScriptEngine*>("ScriptEngine"))
        parent()->findChild<ScriptEngine*>("ScriptEngine")->RunScriptFromString(ui->console_input->toPlainText());


    /**
    *Clear the console
    */
    ui->console_input->clear();


}
