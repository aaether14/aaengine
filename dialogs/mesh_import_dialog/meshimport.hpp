#ifndef MESHIMPORT_HPP
#define MESHIMPORT_HPP





#include <QDebug>
#include <QFileDialog>


#include <dialogs/base_dialog.hpp>
#include <core/glcontroller.hpp>




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
     * @brief MeshImport - basic constructor
     * @param parent
     */
    explicit MeshImport(QWidget *parent = 0);


    /**
    * @brief ~MeshImport - basic destructor
    */
    ~MeshImport();





    /**
     *@brief Reset will reset changes made to default layout (i.e uncheck
     *checked boxes)
     */
    void Reset();





private slots:


    /**
     *@brief on_pushButton_2_clicked will import the mesh with the provided
     *settings
     */
    void on_pushButton_2_clicked();

    /**
     *@brief on_pushButton_clicked will browse for the file you want to import
     */
    void on_pushButton_clicked();

private:



    Ui::MeshImport *ui;




};

#endif // MESHIMPORT_HPP
