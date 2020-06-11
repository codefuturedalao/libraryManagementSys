#include "searchBookDialog.h"
#include <QFormLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include "dbmanagewindow.h"
extern Borrower libUser;

SearchBookDialog::SearchBookDialog(QWidget* parent) :
    QDialog(parent)
{
    setupLayout();
    this->setGeometry(850, 300, 400, 300);
}

void SearchBookDialog::setupLayout() {
    labelBookName = new QLabel("bookName:",this);
    editBookName = new QLineEdit(this);
    btnSearch = new QPushButton("Search", this);
    btnCancel = new QPushButton("Back", this);

    QFormLayout* formLayout = new QFormLayout();
    formLayout->addRow(labelBookName, editBookName);


    QHBoxLayout* btnLayout = new QHBoxLayout();
    btnLayout->addStretch();
    btnLayout->addLayout(formLayout);
    btnLayout->addStretch();
    btnLayout->addWidget(btnSearch);
    btnLayout->addStretch();

    tableWidget = new QTableWidget(5,4);




    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(btnLayout);
    mainLayout->addWidget(tableWidget);
    mainLayout->addWidget(btnCancel);

    // signals and slots
    connect(btnSearch, &QPushButton::clicked, this, &SearchBookDialog::onSearch);
    connect(btnCancel, &QPushButton::clicked, this, &SearchBookDialog::onBack);
}


void SearchBookDialog::onSearch() {
    QString bookName = editBookName->text();

    Title title{bookName.toStdString()};
    if(!title.ExistData()){
            QMessageBox::information(this, "Info", "The Book Doesn't Exist", QMessageBox::Ok);
    }else{
            title.LoadData();
            list<Item *> itemList;
            title.GetItemList(itemList);
            list<Item *>::iterator iter;

            tableWidget->setRowCount(itemList.size()+1);
            tableWidget->setColumnCount(4);
            tableWidget->setItem(0,0,new QTableWidgetItem("BookName"));
            tableWidget->setItem(0,1,new QTableWidgetItem("BookAuthor"));
            tableWidget->setItem(0,2,new QTableWidgetItem("BookItem"));
            tableWidget->setItem(0,3,new QTableWidgetItem("isBorrowedr"));
            int k = 1;
            for(iter = itemList.begin(); iter != itemList.end();++iter){
                tableWidget->setItem(k,0,new QTableWidgetItem(bookName));
                tableWidget->setItem(k,1,new QTableWidgetItem(QString::fromStdString(title.GetAuthor())));
                tableWidget->setItem(k,2,new QTableWidgetItem(QString::fromStdString((*iter)->GetItemId())));
                if((*iter)->IsBorrowed())
                     tableWidget->setItem(k,3,new QTableWidgetItem("true"));
                else
                     tableWidget->setItem(k,3,new QTableWidgetItem("false"));
                k++;
            }
            tableWidget->viewport()->update();
    }

}

void SearchBookDialog::onBack() {
    isCanceled = true;
    this->close();
}

void SearchBookDialog::closeEvent(QCloseEvent *) {
    if (isCanceled) {
        emit sigBack();
    }
}


