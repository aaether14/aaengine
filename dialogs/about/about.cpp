#include <dialogs/about/about.hpp>
#include "ui_about.h"






About::About(QWidget *parent) :
    baseDialog(parent),
    ui(new Ui::About)
{




    ui->setupUi(this);


    /**
     *Every time fps gets computed update it to the dialog
     */
    connect(parent->findChild<FPS*>("gFPS"), SIGNAL(updatedFps(qint32)),
            this, SLOT(ShowFps(qint32)));



}





About::~About()
{

    /**
    *Just delete the ui
    */
    delete ui;

}









void About::ShowFps(const qint32 &fps)
{

    /**
    *Update the fps on the label
    */
    ui->label->setText("Rendering thread fps: " + QString::number(fps));

}
