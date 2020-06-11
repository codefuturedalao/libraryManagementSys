#include "checkInfoDialog.h"
#include <QFormLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include "dbmanagewindow.h"
extern Borrower libUser;

checkInfoDialog::checkInfoDialog(QWidget* parent) :
    QDialog(parent)
{
    setupLayout();
}

void checkInfoDialog::setupLayout() {
    labelBorrowerid = new QLabel("Borrowerid:" + QString::fromStdString(libUser.GetBorrowerId()), this);
    labelUserName = new QLabel("UserName:" + QString::fromStdString(libUser.GetName()),this);
    labelSex = new QLabel("Sex:" + QString::fromStdString(libUser.GetSex()), this);
    labelCity = new QLabel("UserName:" + QString::fromStdString(libUser.GetCity()),this);
    labelAddress = new QLabel("Borrowerid:" + QString::fromStdString(libUser.GetAddress()), this);
    labelBorrowedItem = new QLabel("Borrowed Item List:",this);
    labelReserveTitle = new QLabel("Reservation List:",this);

    libUser.LoadData();
    list<Loan *> loanList;
    list<Loan *>::iterator loanIter;
    list<Reservation *> reservationList;
    list<Reservation *>::iterator reseIter;
    libUser.GetLoanList(loanList);
    libUser.GetReservationList(reservationList);
    QTableWidget *tableWidget = new QTableWidget(loanList.size()+1,2);
    tableWidget->setItem(0,0,new QTableWidgetItem("BookName"));
    tableWidget->setItem(0,1,new QTableWidgetItem("ItemId"));
    int k = 1;
    for(loanIter = loanList.begin();loanIter != loanList.end();++loanIter){
        string itemid = (*loanIter)->GetItemId();
        Item *i = new Item("",itemid);
        i->LoadData();
        tableWidget->setItem(k,0,new QTableWidgetItem(QString::fromStdString(i->GetTitleName())));
        tableWidget->setItem(k,1,new QTableWidgetItem(QString::fromStdString(i->GetItemId())));
        k++;
        delete i;
    }
    QTableWidget *tableWidget1 = new QTableWidget(reservationList.size()+1,1);
    tableWidget1->setItem(0,0,new QTableWidgetItem("BookName"));
    k = 1;
    for(reseIter = reservationList.begin();reseIter != reservationList.end();++reseIter){
        tableWidget1->setItem(k,0,new QTableWidgetItem(QString::fromStdString((*reseIter)->GetTitleName())));
        k++;
    }
    btnBack = new QPushButton("Back", this);

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(labelBorrowerid);
    mainLayout->addWidget(labelUserName);
    mainLayout->addWidget(labelSex);
    mainLayout->addWidget(labelCity);
    mainLayout->addWidget(labelAddress);
    mainLayout->addWidget(labelBorrowedItem);
    mainLayout->addWidget(tableWidget);
    mainLayout->addWidget(labelReserveTitle);
    mainLayout->addWidget(tableWidget1);
    mainLayout->addWidget(btnBack);


    // signals and slots
    connect(btnBack, &QPushButton::clicked, this, &checkInfoDialog::onBack);

}

void checkInfoDialog::onBack(){
    this->close();
}

void checkInfoDialog::closeEvent(QCloseEvent *) {
    emit sigBack();
}


