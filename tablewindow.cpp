//Written by David De Leon
#include "TableWindow.h"

TableWindow::TableWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TableWindow)
{
    ui->setupUi(this);
    /*
     * TODO: remove this next line when there is a proper call to TableWindow
     */
    //emit setEmployee(1234);
}

TableWindow::~TableWindow()
{
    delete ui;
}

/************************************************************************
 * Public slots
 ************************************************************************/

void TableWindow::setEmployee(int emp){
    setEmpNum(emp);
    showTable();
}

/************************************************************************
 * Private slots
 ************************************************************************/

void TableWindow::on_Table01Button_clicked()
{
//    printf("button 01 has been clicked\n");
    tableSelect(1, getEmpNum());
    this->hide();
}

void TableWindow::on_Table02Button_clicked()
{
//    printf("button 02 has been clicked\n");
    tableSelect(2, getEmpNum());
    this->hide();
}

void TableWindow::on_Table03Button_clicked()
{
//    printf("button 03 has been clicked\n");
    tableSelect(3, getEmpNum());
    this->hide();
}

void TableWindow::on_Table04Button_clicked()
{
//    printf("button 04 has been clicked\n");
    tableSelect(4, getEmpNum());
    this->hide();
}

void TableWindow::on_Table05Button_clicked()
{
//    printf("button 05 has been clicked\n");
    tableSelect(5, getEmpNum());
    this->hide();
}

void TableWindow::on_Table06Button_clicked()
{
//    printf("button 06 has been clicked\n");
    tableSelect(6, getEmpNum());
    this->hide();
}

void TableWindow::on_Table07Button_clicked()
{
//    printf("button 07 has been clicked\n");
    tableSelect(7, getEmpNum());
    this->hide();
}

void TableWindow::on_Table08Button_clicked()
{
//    printf("button 08 has been clicked\n");
    tableSelect(8, getEmpNum());
    this->hide();
}

void TableWindow::on_Table09Button_clicked()
{
//    printf("button 09 has been clicked\n");
    tableSelect(9, getEmpNum());
    this->hide();
}

void TableWindow::on_Table10Button_clicked()
{
//    printf("button 10 has been clicked\n");
    tableSelect(10, getEmpNum());
    this->hide();
}

void TableWindow::on_Table11Button_clicked()
{
//    printf("button 11 has been clicked\n");
    tableSelect(11, getEmpNum());
    this->hide();
}

void TableWindow::on_Table12Button_clicked()
{
//    printf("button 12 has been clicked\n");
    tableSelect(12, getEmpNum());
    this->hide();
}

/************************************************************************
 * setters and getters
 ************************************************************************/

int TableWindow::getEmpFromTitle(){
    QString title = windowTitle();
    return -1;
}

void TableWindow::setEmpNum(int emp){
    QString empStr = QString::number(emp);
    ui->empNumLabel->setText(empStr);
    ui->empNumLabel->hide();
}

int TableWindow::getEmpNum(){
    QString numStr = ui->empNumLabel->text();
    int num = numStr.toInt();
    return num;
}


/************************************************************************
 * private methods
 ************************************************************************/

void TableWindow::showTable(){
    FileSystem fs = FileSystem();
    QString title = "Logged in as ";
    int emp = getEmpNum();
    Employee empObj = fs.GetEmployee(emp);
    title += QString::fromStdString(empObj.getEmpName());
    setWindowTitle(title);
    this->show();
}

