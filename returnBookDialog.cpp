#include "returnBookDialog.h"
#include <QFormLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include "dbmanagewindow.h"
extern Borrower libUser;

ReturnBookDialog::ReturnBookDialog(QWidget* parent) :
    QDialog(parent)
{
    setupLayout();
}

void ReturnBookDialog::setupLayout() {
    labelBorrowList = new QLabel("Please select the item you want to return \nBorrowedList:", this);

    btnConfirm = new QPushButton("Confirm", this);
    btnCancel = new QPushButton("Cancel", this);

    libUser.LoadData();
    list<Loan *> loanList;
    list<Loan *>::iterator loanIter;
    list<Reservation *> reservationList;
    list<Reservation *>::iterator reseIter;
    libUser.GetLoanList(loanList);
    libUser.GetReservationList(reservationList);
    tableWidget = new QTableWidget(loanList.size()+1,2);
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

    QHBoxLayout* btnLayout = new QHBoxLayout();
    btnLayout->addStretch();
    btnLayout->addWidget(btnConfirm);
    btnLayout->addStretch();
    btnLayout->addWidget(btnCancel);
    btnLayout->addStretch();

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(labelBorrowList);
    mainLayout->addWidget(tableWidget);
   // mainLayout->addLayout(formLayout);
    mainLayout->addLayout(btnLayout);

    // signals and slots
    connect(btnConfirm, &QPushButton::clicked, this, &ReturnBookDialog::onConfirm);
    connect(btnCancel, &QPushButton::clicked, this, &ReturnBookDialog::onBack);
}


void ReturnBookDialog::onConfirm() {
    QList<QTableWidgetItem*> items = tableWidget->selectedItems();
    int count = items.count();
    for(int i = 0; i < count; i++)
    {
        int row = tableWidget->row(items.at(i));
        QTableWidgetItem *item = items.at(i);
        QString itemid = item->text(); //获取内容
        Loan *loan = new Loan(itemid.toStdString(),libUser.GetBorrowerId());
        if(!loan->ExistData()){
            QMessageBox::information(this, "Info", "the itemid is not correct!", QMessageBox::Ok);
        }else{
                //avoid people return book that don't belong to them
                loan->LoadData();
                if(loan->GetBorrowerId() == libUser.GetBorrowerId()){
                        if(loan->DeleteData()){
                               QMessageBox::information(this, "Info", "successful!", QMessageBox::Ok);
                           //  tableWidget->removeRow(row);
                        }else
                            QMessageBox::information(this, "Info", "Something goes wrong!", QMessageBox::Ok);
                }else{
                    QMessageBox::information(this, "Info", "you haven't borrowed this book, so you cann't return it", QMessageBox::Ok);
                }
        }
        delete loan;

    }
    emit sigReturn();
    this->close();
}

void ReturnBookDialog::onBack() {
    isCanceled = true;
    this->close();
}

void ReturnBookDialog::closeEvent(QCloseEvent *) {
    if (isCanceled) {
        emit sigBack();
    }
}


