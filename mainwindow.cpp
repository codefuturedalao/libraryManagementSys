#include "mainwindow.h"
#include "libraryManage.h"
#include <QVBoxLayout>
#include <QDebug>

Borrower libUser = Borrower();

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupLayout();
    this->setGeometry(850, 300, 200, 100);
}

MainWindow::~MainWindow()
{
}

void MainWindow::setupLayout() {
    QWidget* centralWidget = new QWidget(this);
    this->setCentralWidget(centralWidget);

    btnLogin = new QPushButton("Login", centralWidget);
    btnRegister = new QPushButton("Register", centralWidget);
    systemName = new QLabel("library Management", this);
    systemName->setAlignment(Qt::AlignCenter);

    QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->addWidget(systemName);
    mainLayout->addWidget(btnLogin);
    mainLayout->addWidget(btnRegister);

    // signals and slots
    connect(btnLogin, &QPushButton::clicked, this, &MainWindow::onLogin);
    connect(btnRegister, &QPushButton::clicked, this, &MainWindow::onRegister);
}

void MainWindow::onLogin() {
    LoginDialog* loginDialog = new LoginDialog(nullptr);
    // if login canceled, back to this window
    connect(loginDialog, &LoginDialog::sigCanceled, this, &MainWindow::show);
    // if login successfully, close(destroy) this window
    connect(loginDialog, &LoginDialog::sigLoginOk, this, &MainWindow::close);

    // Attention! hide this window instead of close
    //    only if login successfully, close this window
    //    if login canceled, show this window again
    this->hide();
    loginDialog->show();
}

void MainWindow::onRegister() {
    // show register dialog
    RegisterDialog* registerDialog = new RegisterDialog(nullptr);
    // if login canceled, back to this window
    connect(registerDialog, &RegisterDialog::sigCanceled, this, &MainWindow::show);
    // if login successfully, close(destroy) this window
    connect(registerDialog, &RegisterDialog::sigRegisterOk, this, &MainWindow::close);

    // Attention! hide this window instead of close
    //    only if login successfully, close this window
    //    if login canceled, show this window again
    this->hide();
    registerDialog->show();
}
