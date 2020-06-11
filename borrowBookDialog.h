#ifndef BORROWDIALOG_H
#define BORROWDIALOG_H

#include <QWidget>
#include <QDialog>

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include "libraryManage.h"

class BorrowBookDialog : public QDialog
{
    Q_OBJECT
public:
    BorrowBookDialog(QWidget* parent = nullptr);

signals:
    void sigBack();
    void sigBorrow();

public slots:
    void onBack();
    void onConfirm();

public:
    void setupLayout();

protected:
    virtual void closeEvent(QCloseEvent *) override;

private:
    bool isCanceled = true;

    QLabel* labelItemid;
    QLabel* labelPromptMessage;

    QLineEdit* editItemid;

    QPushButton* btnConfirm;
    QPushButton* btnCancel;
};

#endif // LOGINDIALOG_H
