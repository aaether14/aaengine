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


    ui->lineEdit->clear();


}







void MeshImport::on_pushButton_2_clicked()
{



    /**
    *If no file was provided, no reason to bother to load it
    */


    if (!ui->lineEdit->text().size())
        return;




    /**
    *We need asset loader in order to acces loader library
    */

    if (!parent()->findChild<QObject*>("GL")->findChild<AssetLoader*>("AssetLoader"))
    {
        qDebug() << "MeshImport: Could not find Asset Loader!";
        return;
    }



    /**
     * Get a reference to the asset loader
     */

    AssetLoader * al = parent()->findChild<QObject*>("GL")->findChild<AssetLoader*>("AssetLoader");



    /**
    *Check if there is any loader that can load fbx files
    */

    if (!al->HasLoader("fbx"))
    {
        qDebug() << "MeshImport: Could not find fbx loader!";
        return;
    }




    /**
     *Get a reference to the loader and create a dummy_asset
     */

    FBXManager * fm = static_cast<FBXManager*>(al->GetLoader("fbx"));
    MeshAsset * dummy_asset = static_cast<MeshAsset*>(fm->CreateAsset());




    /**
     * Provided the ui layouy, generate the load options
     */


    QVariantMap load_options;




    load_options["convert_axis"] = ui->checkBox_convert_axis->isChecked();
    load_options["convert_scale"] = ui->checkBox_convert_scale->isChecked();
    load_options["split_points"] = ui->checkBox_split_points->isChecked();
    load_options["generate_tangents"] = ui->checkBox_generate_tangents->isChecked();



    /**
    *Load the fbx file with the provided load options, then delete the dummy
    *asset
    */

    fm->Load(ui->lineEdit->text(), dummy_asset, load_options);
    delete dummy_asset;




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

















