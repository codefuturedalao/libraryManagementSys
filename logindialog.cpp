#include "logindialog.h"
#include <QFormLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include "dbmanagewindow.h"
extern Borrower libUser;

LoginDialog::LoginDialog(QWidget* parent) :
    QDialog(parent)
{
    setupLayout();
}

void LoginDialog::setupLayout() {
    labelBorrowerid = new QLabel("Borrowerid:", this);
    labelPassword = new QLabel("Password:", this);
    editBorrowerid = new QLineEdit(this);
    editPassword = new QLineEdit(this);
    btnLogin = new QPushButton("Login", this);
    btnCancel = new QPushButton("Cancel", this);

    QFormLayout* formLayout = new QFormLayout();
    formLayout->addRow(labelBorrowerid, editBorrowerid);
    formLayout->addRow(labelPassword, editPassword);

    QHBoxLayout* btnLayout = new QHBoxLayout();
    btnLayout->addStretch();
    btnLayout->addWidget(btnLogin);
    btnLayout->addStretch();
    btnLayout->addWidget(btnCancel);
    btnLayout->addStretch();

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(formLayout);
    mainLayout->addLayout(btnLayout);

    // signals and slots
    connect(btnLogin, &QPushButton::clicked, this, &LoginDialog::onLogin);
    connect(btnCancel, &QPushButton::clicked, this, &LoginDialog::onCancel);
}


void LoginDialog::onLogin() {
    QString borrowerid = editBorrowerid->text();
    QString password = editPassword->text();

    // process: login
    // ...
    libUser.SetBorrowerId(borrowerid.toStdString());
    libUser.SetPassword(password.toStdString());


    if (libUser.LoginCheck()) {
        QMessageBox::information(this, "Info", "Login successfully!", QMessageBox::Ok);

        // not canceled, so do not return to the previous window
        isCanceled = false;
        emit sigLoginOk();

        // show other windows
        // and close this window
        // ...
        DbManageWindow* dbManageWindow = new DbManageWindow(nullptr);
        dbManageWindow->show();
        this->close();
    }
    else {
        QMessageBox::information(this, "Info", "Login failed!", QMessageBox::Ok);
    }
}

void LoginDialog::onCancel() {
    isCanceled = true;
    this->close();
}

void LoginDialog::closeEvent(QCloseEvent *) {
    if (isCanceled) {
        emit sigCanceled();
    }
}


