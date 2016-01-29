#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include <QMainWindow>

namespace Ui {
class Controller;
}

class Controller : public QMainWindow
{
    Q_OBJECT

public:
    explicit Controller(QWidget *parent = 0);
    ~Controller();

private:
    Ui::Controller *ui;
};

#endif // CONTROLLER_HPP
