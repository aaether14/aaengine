#include <dialogs/base_dialog.hpp>







baseDialog::baseDialog(QWidget *parent) : QDialog(parent)
{




}




baseDialog::~baseDialog()
{





}





void baseDialog::onAction()
{



    setVisible(!isVisible());


    if (isVisible())
        activateWindow();



}
