#include "borrowBookDialog.h"
#include <QFormLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include "dbmanagewindow.h"
extern Borrower libUser;

BorrowBookDialog::BorrowBookDialog(QWidget* parent) :
    QDialog(parent)
{
    setupLayout();
}

void BorrowBookDialog::setupLayout() {
    labelItemid = new QLabel("Itemid:", this);
    labelPromptMessage = new QLabel("input itemid you want to borrow", this);
    editItemid = new QLineEdit(this);

    btnConfirm = new QPushButton("Confirm", this);
    btnCancel = new QPushButton("Cancel", this);

    QFormLayout* formLayout = new QFormLayout();
    formLayout->addRow(labelItemid, editItemid);

    QHBoxLayout* btnLayout = new QHBoxLayout();
    btnLayout->addStretch();
    btnLayout->addWidget(btnConfirm);
    btnLayout->addStretch();
    btnLayout->addWidget(btnCancel);
    btnLayout->addStretch();

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(labelPromptMessage);
    mainLayout->addLayout(formLayout);
    mainLayout->addLayout(btnLayout);

    // signals and slots
    connect(btnConfirm, &QPushButton::clicked, this, &BorrowBookDialog::onConfirm);
    connect(btnCancel, &QPushButton::clicked, this, &BorrowBookDialog::onBack);
}


void BorrowBookDialog::onConfirm() {
    QString itemid = editItemid->text();

    Item *item = new Item("",itemid.toStdString());
    if(!item->ExistData()){
         QMessageBox::information(this, "Info", "the item doesn't exist, please confirm the itemid", QMessageBox::Ok);
    }else if(item->IsBorrowed()){
         QMessageBox::information(this, "Info", "the item have been borrowed, please switch another book to borrow", QMessageBox::Ok);
    }else{
        Loan *l = new Loan(itemid.toStdString(),libUser.GetBorrowerId());
        if(l->StoreData()){
            QMessageBox::information(this, "Info", "successful!", QMessageBox::Ok);
            //user.AddLoan(l);
        }
        else
            QMessageBox::information(this, "Info", "something goes wrong!", QMessageBox::Ok);

        delete l;
    }
    delete item;


    emit sigBorrow();
    this->close();

}

void BorrowBookDialog::onBack() {
    isCanceled = true;
    this->close();
}

void BorrowBookDialog::closeEvent(QCloseEvent *) {
    if (isCanceled) {
        emit sigBack();
    }
}


