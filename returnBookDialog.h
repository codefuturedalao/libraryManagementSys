#ifndef RETURN_DIALOG_H
#define RETURN_DIALOG_H

#include <QWidget>
#include <QDialog>

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTableWidget>
#include <QTableWidgetItem>
#include "libraryManage.h"

class ReturnBookDialog : public QDialog
{
    Q_OBJECT
public:
    ReturnBookDialog(QWidget* parent = nullptr);

signals:
    void sigBack();
    void sigReturn();

public slots:
    void onBack();
    void onConfirm();

public:
    void setupLayout();

protected:
    virtual void closeEvent(QCloseEvent *) override;

private:
    bool isCanceled = true;

    QLabel* labelBorrowList;
    QTableWidget * tableWidget;

    QPushButton* btnConfirm;
    QPushButton* btnCancel;
};

#endif // LOGINDIALOG_H
