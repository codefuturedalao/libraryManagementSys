#ifndef RE_BOOK_DIALOG_H
#define RE_BOOK_DIALOG_H

#include <QWidget>
#include <QDialog>

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include "libraryManage.h"

class ReDialog : public QDialog
{
    Q_OBJECT
public:
    ReDialog(QWidget* parent = nullptr);

signals:
    void sigBack();
    void sigReOk();

public slots:
    void onRe();
    void onBack();

public:
    void setupLayout();

protected:
    virtual void closeEvent(QCloseEvent *) override;

private:
    bool isCanceled = true;

    QLabel* labelTitleName;

    QLineEdit* editTitleName;

    QPushButton* btnRe;
    QPushButton* btnBack;
};

#endif // AddItemDIALOG_H
