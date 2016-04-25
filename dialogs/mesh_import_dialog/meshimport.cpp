#include <dialogs/mesh_import_dialog/meshimport.hpp>
#include "ui_meshimport.h"






MeshImport::MeshImport(QWidget *parent) :
    baseDialog(parent),
    ui(new Ui::MeshImport)
{


    ui->setupUi(this);


}




MeshImport::~MeshImport()
{


    delete ui;



}





void MeshImport::Reset()
{


    /**
    *Resets layout to default state
    */
    ui->checkBox_convert_axis->setChecked(false);
    ui->checkBox_convert_scale->setChecked(false);
    ui->checkBox_split_points->setChecked(false);
    ui->checkBox_generate_tangents->setChecked(false);
    ui->checkBox_triangulate->setChecked(false);
    ui->checkBox_convert_textures->setChecked(false);
    ui->checkBox_create_aaem->setChecked(false);



    ui->lineEdit->clear();


}







void MeshImport::on_pushButton_2_clicked()
{





#ifdef AAE_USING_FBX
    /**
    *If no file was provided, no reason to bother to load it
    */


    if (!ui->lineEdit->text().size())
        return;




    /**
    *We need asset loader in order to acces loader library
    */

    if (!parent()->findChild<AssetLoader*>("AssetLoader"))
    {
        qDebug() << "MeshImport: Could not find Asset Loader!";
        return;
    }



    /**
     * Get a reference to the asset loader
     */

    AssetLoader * al = parent()->findChild<AssetLoader*>("AssetLoader");



    /**
    *Check if there is any loader that can load fbx files
    */

    if (!al->HasLoader("fbx"))
    {
        qDebug() << "MeshImport: Could not find fbx loader!";
        return;
    }




    /**
     *Get a reference to the loader and create a dummy_mesh
     */




    FBXManager * fm = static_cast<FBXManager*>(al->GetLoader("fbx"));
    Mesh * dummy_mesh = new Mesh();




    if(fm->ImportScene(dummy_mesh, ui->lineEdit->text()))
    {



        dummy_mesh->NormalizeScene(fm->GetManager(),
                                   ui->checkBox_convert_axis,
                                   ui->checkBox_convert_scale,
                                   ui->checkBox_split_points,
                                   ui->checkBox_generate_tangents,
                                   ui->checkBox_triangulate,
                                   ui->checkBox_convert_textures);




        fm->ExportScene(dummy_mesh, ui->lineEdit->text());
        dummy_mesh->ReleaseFbxScene();




        if (ui->checkBox_create_aaem->isChecked())
        {


            if (fm->ImportScene(dummy_mesh, ui->lineEdit->text()))
            {


                dummy_mesh->LoadFromFbxFile(ui->lineEdit->text());



                QFileInfo fbx_file_info(ui->lineEdit->text());
                dummy_mesh->SerializeAAEM(fbx_file_info.path() + "/" + fbx_file_info.baseName() + ".aaem");



                dummy_mesh->ReleaseFbxScene();
                dummy_mesh->ClearGeometryData();


            }


        }




    }





    delete dummy_mesh;



#else
    qDebug() << "FBX importing unavailable on this build! Define AAE_USING_FBX in order to add this feature.";
#endif




    /**
     *After all is done, reset to default layout
     */
    Reset();



}






void MeshImport::on_pushButton_clicked()
{



    /**
    * Check if you can find the GL Controller
    */


    if (!parent()->findChild<GLController*>("GL"))
    {
        qDebug() << "MeshImport: No GL controller detected!";
        return;
    }


    /**
    If GL controller exists, use OpenFileDialog to set the file name for
    further importing
    */


    ui->lineEdit->setText(parent()->findChild<GLController*>("GL")->OpenFileDialog("MeshImport", "*.fbx"));




}

















