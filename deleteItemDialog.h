#ifndef DELETEITEMDIALOG_H
#define DELETEITEMDIALOG_H

#include <QWidget>
#include <QDialog>

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include "libraryManage.h"

class DeleteItemDialog : public QDialog
{
    Q_OBJECT
public:
    DeleteItemDialog(QWidget* parent = nullptr);

signals:
    void sigBack();
    void sigDeleteOk();

public slots:
    void onDelete();
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

    QPushButton* btnDelete;
    QPushButton* btnBack;
};

#endif // DeleteItemDIALOG_H
