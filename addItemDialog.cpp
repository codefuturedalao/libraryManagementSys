#include "addItemDialog.h"
#include <QFormLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include "dbmanagewindow.h"
extern Borrower libUser;

AddItemDialog::AddItemDialog(QWidget* parent) :
    QDialog(parent)
{
    setupLayout();
}

void AddItemDialog::setupLayout() {
    labelTitleName = new QLabel("BookName:", this);
    labelItemid = new QLabel("ItemId:",this);
    editTitleName = new QLineEdit(this);
    editItemid = new QLineEdit(this);

    btnAdd = new QPushButton("Add", this);
    btnBack = new QPushButton("Back", this);

    QFormLayout* formLayout = new QFormLayout();
    formLayout->addRow(labelTitleName, editTitleName);
    formLayout->addRow(labelItemid,editItemid);

    QHBoxLayout* btnLayout = new QHBoxLayout();
    btnLayout->addStretch();
    btnLayout->addWidget(btnAdd);
    btnLayout->addStretch();
    btnLayout->addWidget(btnBack);
    btnLayout->addStretch();

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(formLayout);
    mainLayout->addLayout(btnLayout);

    // signals and slots
    connect(btnAdd, &QPushButton::clicked, this, &AddItemDialog::onAdd);
    connect(btnBack, &QPushButton::clicked, this, &AddItemDialog::onBack);
}


void AddItemDialog::onAdd() {
    QString titleName = editTitleName->text();
    QString itemid = editItemid->text();

    if(libUser.GetIsManager()){
                    Title t = Title(titleName.toStdString());
                    //check whether the title has existed
                    if(t.ExistData()){
                            Item *i = new Item(titleName.toStdString(),itemid.toStdString());
                            if(i->ExistData()){
                                QMessageBox::information(this, "Info", "this item has existed,you cannot add the same item", QMessageBox::Ok);
                            }else{
                                    if(i->StoreData())
                                        QMessageBox::information(this, "Info", "Successful!", QMessageBox::Ok);
                                    else
                                       QMessageBox::information(this, "Info", "Some error happen!", QMessageBox::Ok);
                            }
                            delete i;
                    }else{
                        QMessageBox::information(this, "Info", "the titleName doesn't exist,you cannot add item to a title that doesn't exist", QMessageBox::Ok);
                    }
                        emit sigAddOk();
    }else{
        QMessageBox::information(this, "Info", "You are not Manager!", QMessageBox::Ok);
        this->close();
        emit sigBack();
    }

}

void AddItemDialog::onBack() {
    isCanceled = true;
    this->close();
}

void AddItemDialog::closeEvent(QCloseEvent *) {
    if (isCanceled) {
        emit sigBack();
    }
}


