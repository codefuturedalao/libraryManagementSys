#include <QFormLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <string>
#include "dbmanagewindow.h"

extern Borrower libUser;

DbManageWindow::DbManageWindow(QWidget* parent)
    : QMainWindow(parent)
{
    setupLayout();
    this->setGeometry(850, 300, 400, 300);
}

void DbManageWindow::setupLayout()
{
    QWidget* centralWidget = new QWidget(this);
    this->setCentralWidget(centralWidget);
    //std::cout << libUser.GetName() << std::endl;

    labelUserName = new QLabel(QString::fromStdString(libUser.GetName()),this);
    labelPromtMessge = new QLabel("there some function you can do as follows:",this);
    labelUserName->setAlignment(Qt::AlignCenter);
    labelPromtMessge->setAlignment(Qt::AlignCenter);

    buttonSearchBook = new QPushButton("Search Book");
    buttonBorrowBook = new QPushButton("Borrow Book");
    buttonReturnBook = new QPushButton("Return Book");
    buttonReserveBook = new QPushButton("Reserve Book");
    buttonUnreserveBook = new QPushButton("Unreserve Book");
    buttonAddTitle = new QPushButton("Add Title");
    buttonDeleteTitle = new QPushButton("Delete Title");
    buttonAddItem = new QPushButton("Add Item");
    buttonDeleteItem = new QPushButton("Delete Item");
    buttonCheckInfo = new QPushButton("Check Info");

    QGridLayout* btnLayout = new QGridLayout();
    btnLayout->setSpacing(10);
    btnLayout->addWidget(buttonBorrowBook,0,0);
    btnLayout->addWidget(buttonReturnBook,0,1);
    btnLayout->addWidget(buttonReserveBook,1,0);
    btnLayout->addWidget(buttonUnreserveBook,1,1);
    btnLayout->addWidget(buttonAddItem,2,0);
    btnLayout->addWidget(buttonDeleteItem,2,1);
    btnLayout->addWidget(buttonAddTitle,3,0);
    btnLayout->addWidget(buttonDeleteTitle,3,1);
    btnLayout->addWidget(buttonSearchBook,4,0);
    btnLayout->addWidget(buttonCheckInfo,4,1);

    QVBoxLayout* labelLayout = new QVBoxLayout();
    labelLayout->addWidget(labelUserName);
    labelLayout->addWidget(labelPromtMessge);

    QVBoxLayout * mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->addLayout(labelLayout);
    mainLayout->addLayout(btnLayout);

    connect(buttonBorrowBook, &QPushButton::clicked, this, &DbManageWindow::onBorrowBook);
    connect(buttonReturnBook, &QPushButton::clicked, this, &DbManageWindow::onReturnBook);
    connect(buttonReserveBook, &QPushButton::clicked, this, &DbManageWindow::onReserveBook);
    connect(buttonUnreserveBook, &QPushButton::clicked, this, &DbManageWindow::onUnreserveBook);
    connect(buttonAddItem, &QPushButton::clicked, this, &DbManageWindow::onAddItem);
    connect(buttonDeleteItem, &QPushButton::clicked, this, &DbManageWindow::onDeleteItem);
    connect(buttonAddTitle, &QPushButton::clicked, this, &DbManageWindow::onAddTitle);
    connect(buttonDeleteTitle, &QPushButton::clicked, this, &DbManageWindow::onDeleteTitle);
    connect(buttonSearchBook, &QPushButton::clicked, this, &DbManageWindow::onSearchBook);
    connect(buttonCheckInfo, &QPushButton::clicked, this, &DbManageWindow::onCheckInfo);

}

void DbManageWindow::onSearchBook(){
    SearchBookDialog* searchDialog = new SearchBookDialog(nullptr);

    connect(searchDialog, &SearchBookDialog::sigBack, this, &DbManageWindow::show);
   // connect(searchDialog, &SearchBookDialog::sigBorrow, this, &DbManageWindow::show);

    // Attention! hide this window instead of close
    //    only if login successfully, close this window
    //    if login canceled, show this window again
    this->hide();
    searchDialog->show();

}
void DbManageWindow::onBorrowBook(){
    BorrowBookDialog* borrowDialog = new BorrowBookDialog(nullptr);

    connect(borrowDialog, &BorrowBookDialog::sigBack, this, &DbManageWindow::show);
    connect(borrowDialog, &BorrowBookDialog::sigBorrow, this, &DbManageWindow::show);

    // Attention! hide this window instead of close
    //    only if login successfully, close this window
    //    if login canceled, show this window again
    this->hide();
    borrowDialog->show();
}
void DbManageWindow::onReturnBook(){
    ReturnBookDialog* returnDialog = new ReturnBookDialog(nullptr);

    connect(returnDialog, &ReturnBookDialog::sigBack, this, &DbManageWindow::show);
    connect(returnDialog, &ReturnBookDialog::sigReturn, this, &DbManageWindow::show);

    // Attention! hide this window instead of close
    //    only if login successfully, close this window
    //    if login canceled, show this window again
    this->hide();
    returnDialog->show();
}
void DbManageWindow::onReserveBook(){
    ReDialog* reDialog = new ReDialog(nullptr);

    connect(reDialog, &ReDialog::sigBack, this, &DbManageWindow::show);
    connect(reDialog, &ReDialog::sigReOk, this, &DbManageWindow::show);

    // Attention! hide this window instead of close
    //    only if login successfully, close this window
    //    if login canceled, show this window again
    this->hide();
    reDialog->show();
}
void DbManageWindow::onUnreserveBook(){
    UnreDialog* unreDialog = new UnreDialog(nullptr);

    connect(unreDialog, &UnreDialog::sigBack, this, &DbManageWindow::show);
    connect(unreDialog, &UnreDialog::sigUnreOk, this, &DbManageWindow::show);

    // Attention! hide this window instead of close
    //    only if login successfully, close this window
    //    if login canceled, show this window again
    this->hide();
    unreDialog->show();
}
void DbManageWindow::onAddTitle(){
    AddTitleDialog* addDialog = new AddTitleDialog(nullptr);

    connect(addDialog, &AddTitleDialog::sigBack, this, &DbManageWindow::show);
//    connect(addDialog, &BorrowBookDialog::sigAdd, this, &DbManageWindow::show);

    // Attention! hide this window instead of close
    //    only if login successfully, close this window
    //    if login canceled, show this window again
    this->hide();
    addDialog->show();

}
void DbManageWindow::onDeleteTitle(){
    DeleteTitleDialog* deleteDialog = new DeleteTitleDialog(nullptr);

    connect(deleteDialog, &DeleteTitleDialog::sigBack, this, &DbManageWindow::show);
//    connect(addDialog, &BorrowBookDialog::sigAdd, this, &DbManageWindow::show);

    // Attention! hide this window instead of close
    //    only if login successfully, close this window
    //    if login canceled, show this window again
    this->hide();
    deleteDialog->show();
}
void DbManageWindow::onAddItem(){
    AddItemDialog* addDialog = new AddItemDialog(nullptr);

    connect(addDialog, &AddItemDialog::sigBack, this, &DbManageWindow::show);
//    connect(addDialog, &BorrowBookDialog::sigAdd, this, &DbManageWindow::show);

    // Attention! hide this window instead of close
    //    only if login successfully, close this window
    //    if login canceled, show this window again
    this->hide();
    addDialog->show();
}
void DbManageWindow::onDeleteItem(){
    DeleteItemDialog* deleteDialog = new DeleteItemDialog(nullptr);

    connect(deleteDialog, &DeleteItemDialog::sigBack, this, &DbManageWindow::show);
//    connect(addDialog, &BorrowBookDialog::sigAdd, this, &DbManageWindow::show);

    // Attention! hide this window instead of close
    //    only if login successfully, close this window
    //    if login canceled, show this window again
    this->hide();
    deleteDialog->show();
}
void DbManageWindow::onCheckInfo(){
    checkInfoDialog* checkDialog = new checkInfoDialog(nullptr);

    connect(checkDialog, &checkInfoDialog::sigBack, this, &DbManageWindow::show);


    // Attention! hide this window instead of close
    //    only if login successfully, close this window
    //    if login canceled, show this window again
    this->hide();
    checkDialog->show();

}
