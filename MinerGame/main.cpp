/**
* @file main.cpp
* @ingroup OOPProjectSemester2_1
* @author Egor Polishchuk
* Contact: e-dp@ukr.net
* @version 1.0 12/9/18
*/

/**
* Miner game.
* The rules og game included in resources.
* Player has an oportunity to view them by clicking on help button.
*/

#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
