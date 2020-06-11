#ifndef SEARCHDIALOG_H
#define SEARCHDIALOG_H

#include <QWidget>
#include <QDialog>

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTableWidget>
#include <QTableWidgetItem>
#include "libraryManage.h"

class SearchBookDialog : public QDialog
{
    Q_OBJECT
public:
    SearchBookDialog(QWidget* parent = nullptr);

signals:
    void sigBack();
    void sigBorrow();

public slots:
    void onBack();
    void onSearch();

public:
    void setupLayout();

protected:
    virtual void closeEvent(QCloseEvent *) override;

private:
    bool isCanceled = true;

    QLabel* labelBookName;
    QLineEdit* editBookName;

    QPushButton* btnSearch;
    QPushButton* btnCancel;
    QTableWidget *tableWidget;
};

#endif // SEARCHDIALOG_H
