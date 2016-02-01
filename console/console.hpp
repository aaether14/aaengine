#ifndef CONSOLE_HPP
#define CONSOLE_HPP



#include <script_module/scriptengine.hpp>
#include <console/logger.hpp>
#include <QShortcut>
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

private slots:
    void on_pushButton_clicked();

private:
    Ui::Console *ui;
};

#endif // CONSOLE_HPP
