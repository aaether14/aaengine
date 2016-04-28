#ifndef MESHIMPORT_HPP
#define MESHIMPORT_HPP



#include <aae_defines.hpp>



#include <QDebug>
#include <QFileDialog>



#include <dialogs/base_dialog.hpp>
#include <core/gl/glcontroller.hpp>




namespace Ui {
class MeshImport;
}




/**
 *@brief The MeshImport class will handle the mesh import dialog which will let
 *you set the options for mesh importing and standardizing
 */
class MeshImport : public baseDialog
{


    Q_OBJECT

public:



    /**
     * @brief MeshImport is a basic constructor
     * @param parent is the parent of the QObject
     */
    explicit MeshImport(QWidget *parent = 0);


    /**
    * @brief ~MeshImport is a basic destructor
    */
    ~MeshImport();





    /**
     *@brief Reset will reset changes made to default layout (i.e uncheck
     *checked boxes)
     */
    void Reset();





private slots:



    /**
     * @brief on_browse_button_clicked will browse for the file you want to import
     */
    void on_browse_button_clicked();

    /**
     * @brief on_convert_button_clicked will import the mesh with the provided
     *settings
     */
    void on_convert_button_clicked();



private:


    /**
     * @brief ui is the ui layout of the dialog
     */
    Ui::MeshImport *ui;




};

#endif // MESHIMPORT_HPP
