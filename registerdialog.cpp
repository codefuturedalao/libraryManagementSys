#include "registerdialog.h"
#include <QFormLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include "dbmanagewindow.h"
extern Borrower libUser;

RegisterDialog::RegisterDialog(QWidget* parent) :
    QDialog(parent)
{
    setupLayout();
}

void RegisterDialog::setupLayout() {
    labelBorrowerId = new QLabel("BorrowerId:", this);
    labelPassword = new QLabel("Password:", this);
    labelUserName = new QLabel("Username:", this);
    labelSex = new QLabel("sex(male or female):",this);
    labelAddress = new QLabel("address:",this);
    labelCity = new QLabel("city:",this);

    editBorrowerId = new QLineEdit(this);
    editPassword = new QLineEdit(this);
    editUserName = new QLineEdit(this);
    editSex = new QLineEdit(this);
    editAddress = new QLineEdit(this);
    editCity = new QLineEdit(this);

    btnRegister = new QPushButton("Register", this);
    btnCancel = new QPushButton("Cancel", this);

    QFormLayout* formLayout = new QFormLayout();
    formLayout->addRow(labelBorrowerId, editBorrowerId);
    formLayout->addRow(labelPassword, editPassword);
    formLayout->addRow(labelUserName, editUserName);
    formLayout->addRow(labelSex, editSex);
    formLayout->addRow(labelAddress, editAddress);
    formLayout->addRow(labelCity, editCity);

    QHBoxLayout* btnLayout = new QHBoxLayout();
    btnLayout->addStretch();
    btnLayout->addWidget(btnRegister);
    btnLayout->addStretch();
    btnLayout->addWidget(btnCancel);
    btnLayout->addStretch();

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(formLayout);
    mainLayout->addLayout(btnLayout);

    // signals and slots
    connect(btnRegister, &QPushButton::clicked, this, &RegisterDialog::onRegister);
    connect(btnCancel, &QPushButton::clicked, this, &RegisterDialog::onCancel);
}


void RegisterDialog::onRegister() {
    QString borrowerid = editBorrowerId->text();
    QString username = editUserName->text();
    QString password = editPassword->text();
    QString sex = editSex->text();
    QString address = editAddress->text();
    QString city = editCity->text();

    bool RegisterOk = false;
    // process: login
    // ...
    libUser.SetBorrowerId(borrowerid.toStdString());
    if(libUser.ExistData())
        RegisterOk = false;
    else {
        RegisterOk = true;
        libUser.SetPassword(password.toStdString());
        libUser.SetName(username.toStdString());
        libUser.SetSex(sex.toStdString());
        libUser.SetAddress(address.toStdString());
        libUser.SetCity(city.toStdString());
        libUser.StoreData();
    }
    if (RegisterOk) {
        QMessageBox::information(this, "Info", "Register successfully!", QMessageBox::Ok);

        // not canceled, so do not return to the previous window
        isCanceled = false;
        emit sigRegisterOk();

        // show other windows
        // and close this window
        // ...
        DbManageWindow* dbManageWindow = new DbManageWindow(nullptr);
        dbManageWindow->show();
        this->close();
    }
    else {
        QMessageBox::information(this, "Info", "Register failed!", QMessageBox::Ok);
    }
}

void RegisterDialog::onCancel() {
    isCanceled = true;
    this->close();
}

void RegisterDialog::closeEvent(QCloseEvent *) {
    if (isCanceled) {
        emit sigCanceled();
    }
}


