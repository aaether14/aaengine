#include <console/console.hpp>
#include "ui_console.h"




Console::Console(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Console)
{


    ui->setupUi(this);




    QShortcut *shortcut = new QShortcut(QKeySequence("Ctrl+T"), parent);
    QObject::connect(shortcut, &QShortcut::activated, this, &Console::show);



    ui->splitter->setStretchFactor(0, 2);
    ui->splitter->setStretchFactor(1, 1);




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
