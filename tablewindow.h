//written by David De Leon
#ifndef TABLEWINDOW_H
#define TABLEWINDOW_H

#include <QWidget>
#include "ui_TableWindow.h"
#include "FileSystem.h"

namespace Ui {
class TableWindow;
}

class TableWindow : public QWidget
{
    Q_OBJECT

public:
    explicit TableWindow(QWidget *parent = 0);
    ~TableWindow();

private:
    Ui::TableWindow *ui;
    int getEmpFromTitle();
    void setEmpNum(int);
    int getEmpNum();
    void showTable();

private slots:
    void on_Table01Button_clicked();
    void on_Table02Button_clicked();
    void on_Table03Button_clicked();
    void on_Table04Button_clicked();
    void on_Table05Button_clicked();
    void on_Table06Button_clicked();
    void on_Table07Button_clicked();
    void on_Table08Button_clicked();
    void on_Table09Button_clicked();
    void on_Table10Button_clicked();
    void on_Table11Button_clicked();
    void on_Table12Button_clicked();

public slots:
    void setEmployee(int);

signals:
    void tableSelect(int, int);

};

#endif // TABLEWINDOW_H
