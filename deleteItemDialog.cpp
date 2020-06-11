#include "deleteItemDialog.h"
#include <QFormLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include "dbmanagewindow.h"
extern Borrower libUser;

DeleteItemDialog::DeleteItemDialog(QWidget* parent) :
    QDialog(parent)
{
    setupLayout();
}

void DeleteItemDialog::setupLayout() {
    labelTitleName = new QLabel("BookName:", this);
    labelItemid = new QLabel("ItemId:",this);
    editTitleName = new QLineEdit(this);
    editItemid = new QLineEdit(this);

    btnDelete = new QPushButton("Delete", this);
    btnBack = new QPushButton("Back", this);

    QFormLayout* formLayout = new QFormLayout();
    formLayout->addRow(labelTitleName, editTitleName);
    formLayout->addRow(labelItemid,editItemid);

    QHBoxLayout* btnLayout = new QHBoxLayout();
    btnLayout->addStretch();
    btnLayout->addWidget(btnDelete);
    btnLayout->addStretch();
    btnLayout->addWidget(btnBack);
    btnLayout->addStretch();

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(formLayout);
    mainLayout->addLayout(btnLayout);

    // signals and slots
    connect(btnDelete, &QPushButton::clicked, this, &DeleteItemDialog::onDelete);
    connect(btnBack, &QPushButton::clicked, this, &DeleteItemDialog::onBack);
}


void DeleteItemDialog::onDelete() {
    QString titleName = editTitleName->text();
    QString itemid = editItemid->text();


    if(libUser.GetIsManager()){
                    Title t = Title(titleName.toStdString());
                    //check whether the title has existed
                    if(t.ExistData()){
                            Item *i = new Item(titleName.toStdString(),itemid.toStdString());
                            if(!(i->ExistData())){
                                QMessageBox::information(this, "Info", "this item doesn't existed", QMessageBox::Ok);
                            }else{
                                    if(i->DeleteData())
                                        QMessageBox::information(this, "Info", "Successful!", QMessageBox::Ok);
                                    else
                                       QMessageBox::information(this, "Info", "the item has been borrowed", QMessageBox::Ok);
                            }
                            delete i;
                    }else{
                        QMessageBox::information(this, "Info", "the titleName doesn't exist,you cannot delete item to a title that doesn't exist", QMessageBox::Ok);
                    }
                        emit sigDeleteOk();
    }else{
        QMessageBox::information(this, "Info", "You are not Manager!", QMessageBox::Ok);
        this->close();
        emit sigBack();
    }

}

void DeleteItemDialog::onBack() {
    isCanceled = true;
    this->close();
}

void DeleteItemDialog::closeEvent(QCloseEvent *) {
    if (isCanceled) {
        emit sigBack();
    }
}


