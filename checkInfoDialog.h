#ifndef CHECKINFODIALOG_H
#define CHECKINFODIALOG_H

#include <QWidget>
#include <QDialog>

#include <QLabel>
#include <QPushButton>
#include <QTableWidget>
#include <QTableWidgetItem>
#include "libraryManage.h"

class checkInfoDialog : public QDialog
{
    Q_OBJECT
public:
    checkInfoDialog(QWidget* parent = nullptr);

signals:
    void sigBack();

public slots:
    void onBack();

public:
    void setupLayout();

protected:
    virtual void closeEvent(QCloseEvent *) override;

private:

    QLabel* labelBorrowerid;
    QLabel* labelUserName;
    QLabel* labelSex;
    QLabel* labelCity;
    QLabel* labelAddress;
    QLabel* labelBorrowedItem;
    QTableWidget * borrowedList;
    QLabel* labelReserveTitle;
    QTableWidget * reserveList;


    QPushButton* btnBack;
};

#endif // CHECKINFODIALOG_H
