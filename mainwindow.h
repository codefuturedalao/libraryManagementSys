#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include "logindialog.h"
#include "registerdialog.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void onLogin();
    void onRegister();

public:
    void setupLayout();

private:
    QPushButton* btnLogin = nullptr;
    QPushButton* btnRegister = nullptr;
    QLabel* systemName;

};
#endif // MAINWINDOW_H
