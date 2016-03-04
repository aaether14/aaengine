#ifndef CONSOLE_HPP
#define CONSOLE_HPP



#include <script_module/scriptengine.hpp>
#include <console/logger.hpp>
#include <QShortcut>
#include <QDialog>





namespace Ui {
class Console;
}



/**
 * @brief The Console class will handle the in-game console
 */
class Console : public QDialog
{

    Q_OBJECT

public:

    /**
     * @brief Console will initialize the shortcut and redirect
     * the normal console output to in-game console
     * @param parent
     */
    explicit Console(QWidget *parent = 0);
    /**
      @brief ~Console - basic destructor
    */
    ~Console();


private slots:

    /**
     *@brief on_pushButton_clicked will send the text inside the text edit to
     *the script engine
     */
    void on_pushButton_clicked();

private:


    Ui::Console *ui;
};

#endif // CONSOLE_HPP
