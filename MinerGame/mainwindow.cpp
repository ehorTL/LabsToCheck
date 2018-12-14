#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "field.h"
#include "randomfunctions.h"

#include<QString>
#include<QMessageBox>
#include<QFile>

MainWindow::MainWindow(QWidget *parent) :
                       QMainWindow(parent),
                       ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/img/images/windowIcon1616.ico"));
    setWindowTitle("Miner");
    grid = new field[64];
    startGame();
    setFixedSize(257,281);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete []grid;
}

void MainWindow::isClicked(int k)
{
    if(grid[k].isOpen) return;
    else
    {
        int x,y;
        x = k%columns;
        y = k/columns;
        openCell(x,y);
    }
}

void MainWindow::openCell(int x,int y)
{
    if (x>=columns || y>=strings || x<0 || y<0) return;

    int n = y*columns + x;
    if (grid[n].isOpen) return;

    if (!grid[n].hasBomb && !grid[n].isOpen)
    {
        grid[n].isOpen = true;

        if (grid[n].number == 0)
        {
            QPixmap buttonPix(":/img/images/OpenedEmpty.png");
            grid[n].label->setPixmap(buttonPix);
            grid[n].label->setScaledContents(true);
        }
        else
        {
           QString path = ":/img/images/Opened_" + QString::number(grid[n].number) + ".png";
           QPixmap buttonPix(path);
           grid[n].label->setPixmap(buttonPix);
           grid[n].label->setScaledContents(true);

           if (allCellsOpened())
           {
               QPixmap smile(":/img/images/smileCool.png");
               ui->labelSmile->setPixmap(smile);
               ui->labelSmile->setScaledContents(true);

               int sizeGrid = columns*strings;
               for(int i=0; i<sizeGrid; i++)
               {
                   grid[i].isOpen = true;
               }

               messageWin();
           }

           return;
        }
    }
    else if (grid[n].hasBomb)
    {
        int sizeGrid = columns*strings;
        for(int i=0; i<sizeGrid; i++)
        {
            grid[i].isOpen = true;
            if (grid[i].hasBomb)
            {
                QPixmap buttonPix(":/img/images/OpenedBomb.png");
                grid[i].label->setPixmap(buttonPix);
                grid[i].label->setScaledContents(true);
            }
        }

        QPixmap smile(":/img/images/smileWeeping.png");
        ui->labelSmile->setPixmap(smile);
        ui->labelSmile->setScaledContents(true);

        messageLose();

        return;
    }

    openCell(x-1,y-1);
    openCell(x,y-1);
    openCell(x+1,y-1);
    openCell(x-1,y);
    openCell(x+1,y);
    openCell(x-1, y+1);
    openCell(x,y+1);
    openCell(x+1,y+1);

}

void MainWindow::startGame()
{   
    QPixmap smile(":/img/images/smileQuestion.png");
    ui->labelSmile->setPixmap(smile);
    ui->labelSmile->setScaledContents(true);

    columns = 8;
    strings = 8;
    bombMax = 20;
    bombNumb = 0;  // curent and evetually actual number of bombs on the grid
    int sizeGrid = strings*columns;

    //realized ONLY for sizeGrid==64
    for(int i = 0; i < sizeGrid; i++)
    {
        grid[i].hasBomb = false;
        grid[i].number = 0;
        grid[i].index = i;
        grid[i].label->indexChange(i);
        grid[i].isOpen = false;

        if(i < 8)
        {
            ui->l1->addWidget(grid[i].label);
        }
        else if(i < 16)
        {
            ui->l2->addWidget(grid[i].label);
        }
        else  if(i < 24)
        {
            ui->l3->addWidget(grid[i].label);
        }
       else if(i < 32)
        {
            ui->l4->addWidget(grid[i].label);
        }
        else if(i < 40)
        {
            ui->l5->addWidget(grid[i].label);
        }
        else if(i < 48)
        {
            ui->l6->addWidget(grid[i].label);
        }
        else if(i < 56)
        {
            ui->l7->addWidget(grid[i].label);
        }
        else
        {
            ui->l8->addWidget(grid[i].label);
        }

       QPixmap buttonPix(":/img/images/Closed.png");
       grid[i].label->setPixmap(buttonPix);
       grid[i].label->setScaledContents(true);

       connect(grid[i].label, SIGNAL(clicked(int)), this, SLOT(isClicked(int)));
    }

    // setting bombs
    for (int i=0; i<sizeGrid; i++)
    {
        bool probabilityFactor = get_rand_from_range_incl(1,100) <= (double((double)bombMax/(double)sizeGrid))*100;
        if(probabilityFactor && bombNumb<bombMax)
        {
            grid[i].hasBomb = true;
            bombNumb++;
        }
    }

    //counting numbers in free from bombs cells
    for (int i=0; i<sizeGrid; i++)
    {
        if (grid[i].hasBomb) continue;

        //else
        // 8 cases, maximal number in a cell is 8
        if ( ((i%columns == 0) || i<columns) ? false : grid[i-columns-1].hasBomb) grid[i].number++;
        if ( (i<columns) ? false : grid[i-columns].hasBomb) grid[i].number++;
        if ( (((i+1)%columns == 0) || i<columns) ? false : grid[i-columns+1].hasBomb) grid[i].number++;
        if ( (i%columns == 0) ? false : grid[i-1].hasBomb) grid[i].number++;
        if ( ((i+1)%columns == 0) ? false : grid[i+1].hasBomb) grid[i].number++;
        if ( ((i%columns == 0) || (i >= sizeGrid-columns)) ? false : grid[i+columns-1].hasBomb) grid[i].number++;
        if ( (i >= sizeGrid-columns) ? false : grid[i+columns].hasBomb) grid[i].number++;
        if ( ((i+1)%columns == 0 || (i >= sizeGrid-columns)) ? false : grid[i+columns+1].hasBomb) grid[i].number++;

    }

}

bool MainWindow::allCellsOpened()
{
    int sizeGrid = columns*strings;
    int openCells = 0;
    for (int i=0; i<sizeGrid; i++)
    {
        if (grid[i].isOpen && grid[i].hasBomb) return false;
        if (grid[i].isOpen && !grid[i].hasBomb)
        {
            openCells++;
        }
    }
    return (openCells == sizeGrid-bombNumb);
}


void MainWindow::messageWin()
{
    QMessageBox::information(this, "Congratulations", "You won!!!");
}

void MainWindow::messageLose()
{
    QMessageBox::warning(this, "Oops", "You lose...");
}

int MainWindow::findClosedCellWithoutBomb()
{
    int sizeGrid = columns*strings;
    for (int i=0; i<sizeGrid; i++)
    {
        if (!grid[i].hasBomb && !grid[i].isOpen) return i;
    }
    return -1;
}


void MainWindow::on_pushButtonNewGame_clicked()
{
    startGame();
}

void MainWindow::on_pushButtonHint_clicked()
{
    int indCell = findClosedCellWithoutBomb();
    if (indCell < 0) return;
    //else
    QPixmap tmpHighlight(":/img/images/ClosedHint.png");
    grid[indCell].label->setPixmap(tmpHighlight);
    grid[indCell].label->setScaledContents(true);
}

void MainWindow::on_Info_clicked()
{
    QFile rulesFile;
    QString rulesText;

    rulesFile.setFileName(":/info/text/rules.txt");
    rulesFile.open(QIODevice::ReadOnly | QIODevice::Text);
    while(!rulesFile.atEnd())
    {
        rulesText += rulesFile.readLine();
    }

    QMessageBox::information(this, "RULES", rulesText);
}
