#include <console.hpp>
#include "ui_console.h"




Console::Console(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Console)
{
    ui->setupUi(this);
}




Console::~Console()
{
    delete ui;
}




void Console::on_pushButton_clicked()
{


    parent()->findChild<ScriptEngine*>("ScriptEngine")->RunScriptFromString(ui->textEdit->toPlainText());
    ui->textEdit->clear();


}
