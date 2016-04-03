#include <dialogs/about/about.hpp>
#include "ui_about.h"






About::About(QWidget *parent) :
    baseDialog(parent),
    ui(new Ui::About)
{




    ui->setupUi(this);



    connect(parent->findChild<FPS*>("gFPS"), SIGNAL(updatedFps(int)),
            this, SLOT(ShowFps(int)));



}





About::~About()
{
    delete ui;
}









void About::ShowFps(int fps)
{

    ui->label->setText("Fps: " + QString::number(fps));

}
