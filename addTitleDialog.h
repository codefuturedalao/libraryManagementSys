#ifndef ADDTITLEDIALOG_H
#define ADDTITLEDIALOG_H

#include <QWidget>
#include <QDialog>

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include "libraryManage.h"

class AddTitleDialog : public QDialog
{
    Q_OBJECT
public:
    AddTitleDialog(QWidget* parent = nullptr);

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
    QLabel* labelAuthor;
    QLineEdit* editTitleName;
    QLineEdit* editAuthor;
    QPushButton* btnAdd;
    QPushButton* btnBack;
};

#endif // AddItemDIALOG_H
