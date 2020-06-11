#ifndef DELETETITLEDIALOG_H
#define DELETETITLEDIALOG_H

#include <QWidget>
#include <QDialog>

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include "libraryManage.h"

class DeleteTitleDialog : public QDialog
{
    Q_OBJECT
public:
    DeleteTitleDialog(QWidget* parent = nullptr);

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

    QLineEdit* editTitleName;

    QPushButton* btnDelete;
    QPushButton* btnBack;
};

#endif // AddItemDIALOG_H
