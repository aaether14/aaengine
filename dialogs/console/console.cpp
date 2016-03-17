#include <dialogs/console/console.hpp>
#include "ui_console.h"




Console::Console(QWidget *parent) :
    baseDialog(parent),
    ui(new Ui::Console)
{



    ui->setupUi(this);


    /**
    *Set the stretch factor for the splitter in the console
    */

    ui->splitter->setStretchFactor(0, 2);
    ui->splitter->setStretchFactor(1, 1);


    /**
    *Commence redirecting the console output to in-game console
    */

    Logger::Instance()->setTextEdit(ui->textEdit_2);
    ui->textEdit_2->setTextColor(Qt::red);




}




Console::~Console()
{
    delete ui;
}






void Console::on_pushButton_clicked()
{




    if (parent()->findChild<ScriptEngine*>("ScriptEngine"))
        parent()->findChild<ScriptEngine*>("ScriptEngine")->RunScriptFromString(ui->textEdit->toPlainText());



    ui->textEdit->clear();


}
