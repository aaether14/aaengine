#include <about/about.hpp>
#include "ui_about.h"






About::About(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::About)
{




    ui->setupUi(this);



    connect(parent->findChild<QObject*>("GL")->findChild<FPS*>("gFPS"), SIGNAL(updatedFps(int)),
            this, SLOT(ShowFps(int)));



}





About::~About()
{
    delete ui;
}






void About::onAction()
{



    setVisible(!isVisible());


    if (isVisible())
        activateWindow();



}




void About::ShowFps(int fps)
{

    ui->label->setText("Fps: " + QString::number(fps));

}
