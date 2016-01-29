#ifndef CONSOLE_HPP
#define CONSOLE_HPP

#include <QDialog>

namespace Ui {
class Console;
}

class Console : public QDialog
{
    Q_OBJECT

public:
    explicit Console(QWidget *parent = 0);
    ~Console();

private:
    Ui::Console *ui;
};

#endif // CONSOLE_HPP
