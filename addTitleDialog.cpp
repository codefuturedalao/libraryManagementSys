#include "addTitleDialog.h"
#include <QFormLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include "dbmanagewindow.h"
extern Borrower libUser;

AddTitleDialog::AddTitleDialog(QWidget* parent) :
    QDialog(parent)
{
    setupLayout();
}

void AddTitleDialog::setupLayout() {
    labelTitleName = new QLabel("BookName:", this);
    labelAuthor = new QLabel("Author:",this);
    editTitleName = new QLineEdit(this);
    editAuthor = new QLineEdit(this);
    btnAdd = new QPushButton("Add", this);
    btnBack = new QPushButton("Back", this);

    QFormLayout* formLayout = new QFormLayout();
    formLayout->addRow(labelTitleName, editTitleName);
    formLayout->addRow(labelAuthor,editAuthor);

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
    connect(btnAdd, &QPushButton::clicked, this, &AddTitleDialog::onAdd);
    connect(btnBack, &QPushButton::clicked, this, &AddTitleDialog::onBack);
}


void AddTitleDialog::onAdd() {
    QString titleName = editTitleName->text();
    QString author = editAuthor->text();

    if(libUser.GetIsManager()){
                    Title t = Title(titleName.toStdString(),author.toStdString());
                    if(t.ExistData()){
                        QMessageBox::information(this, "Info", "the title has existed!", QMessageBox::Ok);
                    }else{
                            if(t.StoreData())
                                   QMessageBox::information(this, "Info", "Successful", QMessageBox::Ok);
                            else
                                   QMessageBox::information(this, "Info", "Some Error Happen!", QMessageBox::Ok);

                    }
                        emit sigAddOk();
    }else{
          QMessageBox::information(this, "Info", "You are not Manager!", QMessageBox::Ok);
          this->close();
          emit sigBack();
    }


}

void AddTitleDialog::onBack() {
    isCanceled = true;
    this->close();
}

void AddTitleDialog::closeEvent(QCloseEvent *) {
    if (isCanceled) {
        emit sigBack();
    }
}


