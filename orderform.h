//written by David De Leon

#ifndef ORDERFORM_H
#define ORDERFORM_H

#include <QWidget>
#include "OrderTicket.h"
#include "OrderTicket.h"
#include "MenuItem.h"
#include "FileSystem.h"
#include "ui_OrderForm.h"
#include <string>
#include <QListWidget>
#include <QListWidgetItem>
//#include <QtTest/QTestEvent>
#include <QKeyEvent>
#include <cstdlib>
#include <ctime>
#include <QDebug>
#include <QMessageBox>
#include <QTime>

namespace Ui {
class OrderForm;
}

class OrderForm : public QWidget
{
    Q_OBJECT

public:
    explicit OrderForm(QWidget *parent = 0);
    ~OrderForm();


private:
    double TAX;
    OrderTicket ticket;
    bool menuSetup;
    int getEmpNum();
    void setEmpNum(int emp);
    int getTableNum();
    void setTableNum(int table);
    void showOrderPage();
    void calculateTotals(double subtotal);
    void closeOrder();
    void clearUI();
    void setupUI(int table);
    void setupMenu();
    void addMenuItemToOrder();


private slots:

    void on_AddItemButton_clicked();
    void on_RemoveItemButton_clicked();
    void on_CashOutButton_clicked();
    void on_CancelOrderButton_clicked();
    void on_SaveOrderButton_clicked();
    void on_custSelectSpin_valueChanged(int custNum);
    void on_testButton_clicked();
    void on_OrderTabWidget_currentChanged(int index);

public slots:
    void setTable(int table, int emp);

private:
    Ui::OrderForm *ui;

protected:
    bool eventFilter(QObject *obj, QEvent *event);
//    void keyPressEvent(QKeyEvent* pe);

signals:
    void endSession();
};

#endif // ORDERFORM_H
