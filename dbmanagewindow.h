#ifndef DBMANAGEWINDOW_H
#define DBMANAGEWINDOW_H

#include <QWidget>
#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include "libraryManage.h"
#include "checkInfoDialog.h"
#include "borrowBookDialog.h"
#include "searchBookDialog.h"
#include "addItemDialog.h"
#include "addTitleDialog.h"
#include "deleteItemDialog.h"
#include "deleteTitleDialog.h"
#include "returnBookDialog.h"
#include "reserveBookDialog.h"
#include "unreserveBookDialog.h"

class DbManageWindow : public QMainWindow
{
    Q_OBJECT
public:
    DbManageWindow(QWidget* parent = nullptr);
    void setupLayout();

public slots:
    void onSearchBook();
    void onBorrowBook();
    void onReturnBook();
    void onReserveBook();
    void onUnreserveBook();
    void onAddTitle();
    void onDeleteTitle();
    void onAddItem();
    void onDeleteItem();
    void onCheckInfo();

private:
    QLabel* labelUserName;
    QLabel* labelPromtMessge;

    QPushButton * buttonSearchBook;
    QPushButton * buttonBorrowBook;
    QPushButton * buttonReturnBook;
    QPushButton * buttonReserveBook;
    QPushButton * buttonUnreserveBook;
    QPushButton * buttonAddTitle;
    QPushButton * buttonDeleteTitle;
    QPushButton * buttonAddItem;
    QPushButton * buttonDeleteItem;
    QPushButton * buttonCheckInfo;
};

#endif // DBMANAGEWINDOW_H
