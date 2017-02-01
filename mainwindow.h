
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include "TableWindow.h"
#include "ui_MainWindow.h"
#include "Employee.h"
#include "FileSystem.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

//protected slots:
//    void employeeLogin();
private slots:
    void on_loginButton_clicked();
    void on_Clear_clicked();
    void on_clockButton_clicked();

private:
    Ui::MainWindow *ui;

signals:
    void employeeSelect(int);

public slots:
    void showLogin();
};

#endif // MAINWINDOW_H
