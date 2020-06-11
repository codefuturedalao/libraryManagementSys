#include "unreserveBookDialog.h"
#include <QFormLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include "dbmanagewindow.h"
extern Borrower libUser;

UnreDialog::UnreDialog(QWidget* parent) :
    QDialog(parent)
{
    setupLayout();
}

void UnreDialog::setupLayout() {
    labelTitleName = new QLabel("BookName:", this);
    labelReserveTitle = new QLabel("Reservation List:",this);
    editTitleName = new QLineEdit(this);

    btnUnre = new QPushButton("Unreserve", this);
    btnBack = new QPushButton("Back", this);

    QFormLayout* formLayout = new QFormLayout();
    formLayout->addRow(labelTitleName, editTitleName);

    QHBoxLayout* btnLayout = new QHBoxLayout();
    btnLayout->addStretch();
    btnLayout->addWidget(btnUnre);
    btnLayout->addStretch();
    btnLayout->addWidget(btnBack);
    btnLayout->addStretch();

    list<Reservation *> reservationList;
    list<Reservation *>::iterator reseIter;
    libUser.GetReservationList(reservationList);
    QTableWidget *tableWidget1 = new QTableWidget(reservationList.size()+1,1);
    tableWidget1->setItem(0,0,new QTableWidgetItem("BookName"));
    int k = 1;
    for(reseIter = reservationList.begin();reseIter != reservationList.end();++reseIter){
        tableWidget1->setItem(k,0,new QTableWidgetItem(QString::fromStdString((*reseIter)->GetTitleName())));
        k++;
    }
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(formLayout);
    mainLayout->addWidget(labelReserveTitle);
    mainLayout->addWidget(tableWidget1);
    mainLayout->addLayout(btnLayout);

    // signals and slots
    connect(btnUnre, &QPushButton::clicked, this, &UnreDialog::onUnre);
    connect(btnBack, &QPushButton::clicked, this, &UnreDialog::onBack);
}


void UnreDialog::onUnre() {
    QString titleName = editTitleName->text();
    if(libUser.GetIsManager()){
                    Title t = Title(titleName.toStdString());
                    if(!t.ExistData()){
                        QMessageBox::information(this, "Info", "the book doesn't exist!", QMessageBox::Ok);
                    }else{
                            Reservation *r = new Reservation(titleName.toStdString(),libUser.GetBorrowerId());
                            if(r->GetBorrowerId() == libUser.GetBorrowerId()){
                                if(r->DeleteData())
                                       QMessageBox::information(this, "Info", "Successful", QMessageBox::Ok);
                                else
                                       QMessageBox::information(this, "Info", "Some Error Happen!", QMessageBox::Ok);
                            }else {
                              QMessageBox::information(this, "Info", "this book is not in you reservation list", QMessageBox::Ok);
                            }
                    }
                        emit sigUnreOk();
    }else{
          QMessageBox::information(this, "Info", "You are not Manager!", QMessageBox::Ok);
          emit sigBack();
    }

    this->close();
}

void UnreDialog::onBack() {
    isCanceled = true;
    this->close();
}

void UnreDialog::closeEvent(QCloseEvent *) {
    if (isCanceled) {
        emit sigBack();
    }
}


