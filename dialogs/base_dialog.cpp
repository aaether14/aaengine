#include <dialogs/base_dialog.hpp>







baseDialog::baseDialog(QWidget *parent) : QDialog(parent)
{



    /**
    *The glorious nothing...
    */



}




baseDialog::~baseDialog()
{


    /**
    *The glorious nothing...
    */



}





void baseDialog::onAction()
{


    /**
     *If the dialog is hidden show it, if it's visible hide it
     */
    setVisible(!isVisible());


    /**
    *If the dialog has just been made visible, focus it
    */
    if (isVisible())
        activateWindow();



}
