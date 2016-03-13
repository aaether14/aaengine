#ifndef MESHIMPORT_HPP
#define MESHIMPORT_HPP



#include <QDialog>




namespace Ui {
class MeshImport;
}




/**
 *@brief The MeshImport class will handle the mesh import dialog which will let
 *you set the options for mesh importing and standardizing
 */
class MeshImport : public QDialog
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
    * @brief onAction will determine what About will do when about action is
    *triggered
     */
    void onAction();


    /**
     *@brief Reset will reset changes made to default layout (i.e uncheck
     *checked boxes)
     */
    void Reset();





private:



    Ui::MeshImport *ui;




};

#endif // MESHIMPORT_HPP
