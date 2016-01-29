#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP



#include <QMainWindow>
#include <glcontroller.hpp>
#include <console.hpp>
#include <scriptengine.hpp>





namespace Ui {
class Controller;
}




class Controller : public QMainWindow
{
    Q_OBJECT

public:
    explicit Controller(QWidget *parent = 0);
    ~Controller();

private slots:
    void on_actionConsole_triggered();

private:
    Ui::Controller *ui;
};







#endif // CONTROLLER_HPP
