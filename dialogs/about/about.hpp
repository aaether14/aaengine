#ifndef ABOUT_HPP
#define ABOUT_HPP



#include <core/gl/fps.hpp>
#include <dialogs/base_dialog.hpp>




namespace Ui {
class About;
}



/**
 *@brief The About class will hold an ui containing useful information about
 *the app
 */
class About : public baseDialog
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




private:
    Ui::About *ui;



public slots:


    /**
     * @brief ShowFps will update the fps display
     * @param fps
     */
    void ShowFps(const qint32 &fps);




};

#endif // ABOUT_HPP
