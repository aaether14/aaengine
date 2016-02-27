#ifndef ABOUT_HPP
#define ABOUT_HPP



#include <QDialog>
#include <QShortcut>
#include <core/fps.hpp>





namespace Ui {
class About;
}

class About : public QDialog
{


    Q_OBJECT



public:
    explicit About(QWidget *parent = 0);
    ~About();



private:
    Ui::About *ui;



public slots:
    void ShowFps(int fps);




};

#endif // ABOUT_HPP
