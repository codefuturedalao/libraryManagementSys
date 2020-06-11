#ifndef REGISTERDIALOG_H
#define REGISTERDIALOG_H

#include <QWidget>
#include <QDialog>

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include "libraryManage.h"

class RegisterDialog : public QDialog
{
    Q_OBJECT
public:
    RegisterDialog(QWidget* parent = nullptr);

signals:
    void sigCanceled();
    void sigRegisterOk();

public slots:
    void onRegister();
    void onCancel();

public:
    void setupLayout();

protected:
    virtual void closeEvent(QCloseEvent *) override;

private:
    bool isCanceled = true;

    QLabel* labelBorrowerId;
    QLabel* labelPassword;
    QLabel* labelUserName;
    QLabel* labelSex;
    QLabel* labelAddress;
    QLabel* labelCity;

    QLineEdit* editBorrowerId;
    QLineEdit* editPassword;
    QLineEdit* editUserName;
    QLineEdit* editSex;
    QLineEdit* editAddress;
    QLineEdit* editCity;

    QPushButton* btnRegister;
    QPushButton* btnCancel;
};

#endif // LOGINDIALOG_H
