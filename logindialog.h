#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QWidget>
#include <QDialog>

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include "libraryManage.h"

class LoginDialog : public QDialog
{
    Q_OBJECT
public:
    LoginDialog(QWidget* parent = nullptr);

signals:
    void sigCanceled();
    void sigLoginOk();

public slots:
    void onLogin();
    void onCancel();

public:
    void setupLayout();

protected:
    virtual void closeEvent(QCloseEvent *) override;

private:
    bool isCanceled = true;

    QLabel* labelBorrowerid;
    QLabel* labelPassword;

    QLineEdit* editBorrowerid;
    QLineEdit* editPassword;

    QPushButton* btnLogin;
    QPushButton* btnCancel;
};

#endif // LOGINDIALOG_H
