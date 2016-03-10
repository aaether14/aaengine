#ifndef ABOUT_HPP
#define ABOUT_HPP



#include <QDialog>
#include <core/fps.hpp>





namespace Ui {
class About;
}



/**
 *@brief The About class will hold an ui containing useful information about
 *the app
 */
class About : public QDialog
{


    Q_OBJECT



public:


    /**
     * @brief About will initialize shortcut and set
     * to update the fps display every frame
     * @param parent
     */
    explicit About(QWidget *parent = 0);
    ~About();



    /**
     *@brief onAction will determine what About will do when about action is
     *triggered
     */
    void onAction();




private:
    Ui::About *ui;



public slots:


    /**
     * @brief ShowFps will update the fps display
     * @param fps
     */
    void ShowFps(int fps);




};

#endif // ABOUT_HPP
