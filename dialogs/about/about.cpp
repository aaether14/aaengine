#include <dialogs/about/about.hpp>
#include "ui_about.h"






About::About(QWidget *parent) :
    baseDialog(parent),
    ui(new Ui::About)
{




    ui->setupUi(this);



    connect(parent->findChild<FPS*>("gFPS"), SIGNAL(updatedFps(qint32)),
            this, SLOT(ShowFps(qint32)));



}





About::~About()
{
    delete ui;
}









void About::ShowFps(qint32 fps)
{

    ui->label->setText("Fps: " + QString::number(fps));

}
