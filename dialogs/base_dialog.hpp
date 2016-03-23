#ifndef BASE_DIALOG_H
#define BASE_DIALOG_H




#include <QDialog>




/**
 *@brief The baseDialog class will serve for defining basic dialog properties
 *troughout the engine
 */
class baseDialog : public QDialog
{



    Q_OBJECT



public:


    /**
     * @brief baseDialog - basic constructor
     * @param parent
     */
    explicit baseDialog(QWidget *parent = 0);


    /**
     * @brief ~baseDialog - basic destructor
     */
    virtual ~baseDialog();




public slots:


    /**
     *@brief onAction will determine what the dialog will do when the action
     *regarding it will be triggered
     */
    virtual void onAction();



};

#endif // BASE_DIALOG_H
