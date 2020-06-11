#ifndef UNRE_BOOK_DIALOG_H
#define UNRE_BOOK_DIALOG_H

#include <QWidget>
#include <QDialog>

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTableWidget>
#include <QTableWidgetItem>
#include "libraryManage.h"

class UnreDialog : public QDialog
{
    Q_OBJECT
public:
    UnreDialog(QWidget* parent = nullptr);

signals:
    void sigBack();
    void sigUnreOk();

public slots:
    void onUnre();
    void onBack();

public:
    void setupLayout();

protected:
    virtual void closeEvent(QCloseEvent *) override;

private:
    bool isCanceled = true;

    QLabel* labelTitleName;

    QLineEdit* editTitleName;
    QLabel* labelReserveTitle;
    QTableWidget * reserveList;
    QPushButton* btnUnre;
    QPushButton* btnBack;
};

#endif // AddItemDIALOG_H
