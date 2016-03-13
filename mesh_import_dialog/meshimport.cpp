#include <mesh_import_dialog/meshimport.hpp>
#include "ui_meshimport.h"






MeshImport::MeshImport(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MeshImport)
{


    ui->setupUi(this);


}




MeshImport::~MeshImport()
{


    delete ui;



}




void MeshImport::onAction()
{



    setVisible(!isVisible());


    if (isVisible())
        activateWindow();



}



void MeshImport::Reset()
{





}
