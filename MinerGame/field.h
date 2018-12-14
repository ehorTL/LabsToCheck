#ifndef FIELD_H
#define FIELD_H

#include <QDialog>
#include<QLabel>

/**
* Implement a label with specified for field class event handler.
* Derived from QLabel class (public).
*
* Data: int index.
*/
class ClickableLabel : public QLabel
{
    Q_OBJECT
public:
    explicit ClickableLabel(QWidget* parent=nullptr);
    ~ClickableLabel();

    void indexChange(int);      ///< Sets index (equal to received value). Index of field obejct.
    int index;                  ///< Unique index of the label. Used for click tracking.

signals:
    void clicked(int);          ///< Emits signal clicked().

protected:
    void mousePressEvent(QMouseEvent* event);
};



/**
* Implement a cell of gare grid.
* Derived from QDialog class (public).
*
* Data: int index, bool hasBomb, int number, ClicableLabel *label.
* Methods: bool isOpen().
*/
class field : public QDialog
{
    Q_OBJECT
public:
    explicit field(QWidget *parent = nullptr);
    ~field();

    int index;             ///< uniquie cell (field) index (in array)
    bool hasBomb;          ///< if cell has bomb or not
    int number;            ///< bombs quantity (sum) in neighbouring fileds
    ClickableLabel *label; ///< label for image and clicking possibility

    bool isOpen;           ///< checks if field was already opened by user
};


#endif // FIELD_H
