//
// Written by Andrew Behncke, edited by David
//
#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_loginButton_clicked()
{
    QString id = ui->empID->text();
    int idNum = id.toInt(0, 10);
    FileSystem fs = FileSystem();
    Employee currentEmployee = fs.GetEmployee(idNum);
    if (currentEmployee.getEmpName() == Employee().getEmpName()){
        QMessageBox alert;
        alert.setText("Invalid ID. Please try again");
        alert.setWindowTitle("Error");
        alert.exec();
    } else {
        employeeSelect(currentEmployee.getEmpNum());
        this->hide();
    }
}

void MainWindow::showLogin(){
    ui->empID->setText("");
    this->show();
}

void MainWindow::on_Clear_clicked()
{
    ui->empID->setText("");
    ui->empID->setFocus();
}

void MainWindow::on_clockButton_clicked()
{
    QString id = ui->empID->text();
    int idNum = id.toInt(0, 10);
    FileSystem fs = FileSystem();
    Employee currentEmployee = fs.GetEmployee(idNum);
    ui->empID->setFocus();
}
