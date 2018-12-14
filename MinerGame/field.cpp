#include "field.h"

field::field(QWidget *parent) : QDialog(parent)
{
    hasBomb = false;
    index = -1;
    number = 0;
    label = new ClickableLabel; // label of the button

    isOpen = false;
}

field::~field()
{
}

ClickableLabel::ClickableLabel(QWidget* parent) : QLabel(parent)
{
    QPixmap buttonPix(":/img/images/Closed.png"); // picture on a button when cell is unopened
    this->setPixmap(buttonPix);
    this->setScaledContents(true);
}

ClickableLabel::~ClickableLabel()
{
}

void ClickableLabel::mousePressEvent(QMouseEvent* event)
{
    emit clicked(index);
}

void ClickableLabel::indexChange(int i)
{
    index = i;
}




