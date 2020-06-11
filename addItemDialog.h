#ifndef ADDITEMDIALOG_H
#define ADDITEMDIALOG_H

#include <QWidget>
#include <QDialog>

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include "libraryManage.h"

class AddItemDialog : public QDialog
{
    Q_OBJECT
public:
    AddItemDialog(QWidget* parent = nullptr);

signals:
    void sigBack();
    void sigAddOk();

public slots:
    void onAdd();
    void onBack();

public:
    void setupLayout();

protected:
    virtual void closeEvent(QCloseEvent *) override;

private:
    bool isCanceled = true;

    QLabel* labelTitleName;
    QLabel* labelItemid;

    QLineEdit* editTitleName;
    QLineEdit* editItemid;

    QPushButton* btnAdd;
    QPushButton* btnBack;
};

#endif // AddItemDIALOG_H
