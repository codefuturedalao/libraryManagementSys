#include "reserveBookDialog.h"
#include <QFormLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include "dbmanagewindow.h"
extern Borrower libUser;

ReDialog::ReDialog(QWidget* parent) :
    QDialog(parent)
{
    setupLayout();
}

void ReDialog::setupLayout() {
    labelTitleName = new QLabel("BookName:", this);

    editTitleName = new QLineEdit(this);

    btnRe = new QPushButton("Reserve", this);
    btnBack = new QPushButton("Back", this);

    QFormLayout* formLayout = new QFormLayout();
    formLayout->addRow(labelTitleName, editTitleName);


    QHBoxLayout* btnLayout = new QHBoxLayout();
    btnLayout->addStretch();
    btnLayout->addWidget(btnRe);
    btnLayout->addStretch();
    btnLayout->addWidget(btnBack);
    btnLayout->addStretch();

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(formLayout);
    mainLayout->addLayout(btnLayout);

    // signals and slots
    connect(btnRe, &QPushButton::clicked, this, &ReDialog::onRe);
    connect(btnBack, &QPushButton::clicked, this, &ReDialog::onBack);
}


void ReDialog::onRe() {
    QString titleName = editTitleName->text();

    if(libUser.GetIsManager()){
                    Title t = Title(titleName.toStdString());
                    if(!t.ExistData()){
                        QMessageBox::information(this, "Info", "the book doesn't exist!", QMessageBox::Ok);
                    }else{
                            Reservation *r = new Reservation(titleName.toStdString(),libUser.GetBorrowerId());
                            if(r->StoreData())
                                   QMessageBox::information(this, "Info", "Successful", QMessageBox::Ok);
                            else
                                   QMessageBox::information(this, "Info", "Some Error Happen!", QMessageBox::Ok);

                    }
                        emit sigReOk();
    }else{
          QMessageBox::information(this, "Info", "You are not Manager!", QMessageBox::Ok);
          emit sigBack();
    }
    this->close();

}

void ReDialog::onBack() {
    isCanceled = true;
    this->close();
}

void ReDialog::closeEvent(QCloseEvent *) {
    if (isCanceled) {
        emit sigBack();
    }
}


