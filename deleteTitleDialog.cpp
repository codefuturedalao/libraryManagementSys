#include "deleteTitleDialog.h"
#include <QFormLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include "dbmanagewindow.h"
extern Borrower libUser;

DeleteTitleDialog::DeleteTitleDialog(QWidget* parent) :
    QDialog(parent)
{
    setupLayout();
}

void DeleteTitleDialog::setupLayout() {
    labelTitleName = new QLabel("BookName:", this);

    editTitleName = new QLineEdit(this);

    btnDelete = new QPushButton("Delete", this);
    btnBack = new QPushButton("Back", this);

    QFormLayout* formLayout = new QFormLayout();
    formLayout->addRow(labelTitleName, editTitleName);


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
    connect(btnDelete, &QPushButton::clicked, this, &DeleteTitleDialog::onDelete);
    connect(btnBack, &QPushButton::clicked, this, &DeleteTitleDialog::onBack);
}


void DeleteTitleDialog::onDelete() {
    QString titleName = editTitleName->text();


    if(libUser.GetIsManager()){
                    Title t = Title(titleName.toStdString());
                    if(!(t.ExistData())){
                        QMessageBox::information(this, "Info", "the title doesn't exist!", QMessageBox::Ok);
                    }else{
                        t.LoadData();
                            if(t.IsReserved())
                                QMessageBox::information(this, "Info", "book has been reserved, can not delete", QMessageBox::Ok);
                            else if(t.DeleteData())
                                   QMessageBox::information(this, "Info", "Successful", QMessageBox::Ok);
                            else
                                   QMessageBox::information(this, "Info", "some items of this book have been borrowed,can not delete this book!", QMessageBox::Ok);

                    }
                        emit sigDeleteOk();
    }else{
          QMessageBox::information(this, "Info", "You are not Manager!", QMessageBox::Ok);
          this->close();
          emit sigBack();
    }


}

void DeleteTitleDialog::onBack() {
    isCanceled = true;
    this->close();
}

void DeleteTitleDialog::closeEvent(QCloseEvent *) {
    if (isCanceled) {
        emit sigBack();
    }
}


