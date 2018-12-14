#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "field.h"

namespace Ui
{
    class MainWindow;
}

/**
* The main program window.
* Implements game grid (composed of field objects) and methods available for user to interact.
* Contains the sequenece of fields (showed as cells).
*/
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
/**
* Allocates memory for game grid (sequence of field objects).
* Tune window tittle and window icon.
* Calls startGame() function.
*/
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
/**
* Starts new game. Initialize and sets all variables equal to values
* defined by game rules.
*/
    void startGame();

private:
    Ui::MainWindow *ui;
    field *grid;                ///< Grig of fields. Array of king: new field[strings*columns];
    int strings, columns;       ///< define dimentions of the grid
    int bombMax;                ///< upper bound of bombs quantity
    int bombNumb;               ///< actual quantity of bombs on the grid

/**
* Recursive function.
* Opens current cell if it is not opened.
* Does nothing is current cell is already open.
* If current cell is empty, all neighbouring empty cells are opened, and then
* around them are opened cells with numbers.
* Algorithm are called recursively for every "next" cell.
*/
    void openCell(int x, int y);

/**
* Returns if all fields are open (checks all variables isOpen).
* @return all fields isOpen variables == true.
*/
    bool allCellsOpened();

/**
* Notify user is winner. Game over.
* Calls QMessageBox::information().
*/
    void messageWin();

/**
* Notify the user is loser. Game over.
* Calls QMessageBox::warning().
*/
    void messageLose();

/**
* Finds the next not opened cell from the beginning of grid array.
* @return index of closed field without bomb,
*         0<=index<=63 in case such cell found, -1 else.
*/
    int findClosedCellWithoutBomb();

private slots:
/**
* Calls openCell() function in case current clicked field
* has not been opened
*/
    void isClicked(int);

/**
* When pushButtonNewGame is pushed, function is called.
* Calls startGame() function.
*/
    void on_pushButtonNewGame_clicked();

/**
* Highlights next from beginning not opened cell without bomb.
* The cell is overlight until it opened.
* Next hint is not shown until current one is not used (current cell is not opened by user).
*/
    void on_pushButtonHint_clicked();

/**
* Calls the QMessage::information() function.
* Shows the .txt file with rules with logic path to it ":/info/text/rules.txt".
*/
    void on_Info_clicked();
};

#endif // MAINWINDOW_H
