/*written by David De Leon
 * This is the UI class for the order page, and it contains most of the logic
 * for handling the orders in the UI.
*/
#include "OrderForm.h"


OrderForm::OrderForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OrderForm)
{
    TAX = .06;
    menuSetup = false;
    ui->setupUi(this);
}

OrderForm::~OrderForm()
{
    delete ui;
}

/************************************************************************
 * Public slots
 ************************************************************************/

//this function is called when a table button is clicked on the TableWindow UI
//it begins the process of setting up the OrderForm UI for use
void OrderForm::setTable(int table, int emp){
    setEmpNum(emp);
    setTableNum(table);
    QTime qtime = QTime::currentTime();
    int hour = qtime.hour();
    int min = qtime.minute();
    //sets time to a double representing time as hour.minute
    double timed = hour + (min/100.0);
    ticket.setOrderTime(timed);
    setupUI(table);
    showOrderPage();

}

/************************************************************************
 * Private slots
 ************************************************************************/

//This function is called anytime the Add Item button is pressed in the OrderForm
//UI window, when the UI is being built by setupUI, or when the test button is pressed
//It adds the requested item (if valid) to the UI and to the ticket object
void OrderForm::on_AddItemButton_clicked()
{
    FileSystem fs = FileSystem();
    QString item = ui->MenuItemEdit->text();
    //if nothing has been entered in, end execution
    if(item.isEmpty()){
        QMessageBox alert;
        alert.setText("You did not enter anything. Please try again");
        alert.setWindowTitle("Error");
        alert.exec();
        return;
    }
    int idNum = item.toInt();
    MenuItem chosenItem;
    //handle string based names
    if(idNum == 0){
        if(fs.IsValidMenuItem(item.toStdString()))
            chosenItem = fs.GetMenuItem(item.toStdString());
        else{
            QMessageBox alert;
            alert.setText("The MenuItem '" + item + "' is invalid. Please try again");
            alert.setWindowTitle("Error");
            alert.exec();
            return;
        }
    }else{ //handle int IDs
        if(fs.IsValidMenuItem(idNum))
            chosenItem = fs.GetMenuItem(idNum);
        else{
            QMessageBox alert;
            alert.setText("The MenuItem ID '" + QString::number(idNum)
                          + "' invalid. Please try again");
            alert.setWindowTitle("Error");
            alert.exec();
            return;
        }
    }

    //add the item to the GUI
    item = QString::fromStdString(chosenItem.getItemDesc());
//    int quantity = ui->quantSpin->value();
    item += ", $" + QString::number(chosenItem.getItemPrice());
    int customer = ui->custSpin->value();
    item += ", cust #" + QString::number(customer);
    new QListWidgetItem(item, ui->listWidget, 0);
    ticket.addItemToOrder(customer, chosenItem);
    //recalculate order
    double tot = ticket.calculateOrder();
    calculateTotals(tot);

}

//This function is called anytime the Remove Item button is pressed in the OrderForm
//UI window. It removes the selected item from the UI and from the ticket object
void OrderForm::on_RemoveItemButton_clicked()
{
    //check if the current tab is the Menu tab, and run a different function if it is
    if(ui->OrderTabWidget->currentIndex() == 1){
        addMenuItemToOrder();
        return;
    }

    int row = ui->listWidget->currentRow();
    //if there is no item selected, stop
    if(row==-1)
        return;
    QListWidgetItem * rem = ui->listWidget->takeItem(row);
    //remove the item from the ticket
    QString item = rem->text();
    QStringList itemList = item.split(",");
    item = itemList.at(0);
    FileSystem fs = FileSystem();
    int itemId = fs.GetMenuItem(item.toStdString()).getItemId();
    item = itemList.at(2).split("#").at(1);
    int cust = item.toInt(0, 10);
    ticket.removeItem(cust, itemId);

    //recalculate order
    calculateTotals(ticket.calculateOrder());
}

void OrderForm::on_CashOutButton_clicked()
{
    FileSystem fs = FileSystem();
    fs.finalReceipt(&ticket);
    closeOrder();
}

//This function is called anytime the Cancel Order button is pressed in the OrderForm
//UI window.This functions deletes any existing order file, and returns to the
//login screen
void OrderForm::on_CancelOrderButton_clicked()
{
    FileSystem fs = FileSystem();
    std::stringstream filename;
    filename << "Order" << ticket.getOrderId() << ".txt";
    fs.DeleteFile(filename.str());
    closeOrder();
}

//This function saves the current order to a file and returns to the login screen
void OrderForm::on_SaveOrderButton_clicked()
{
    FileSystem fs = FileSystem();
    fs.SaveOrderTicket(&ticket);
    closeOrder();
}

//This function is called anytime the customer selection spinner in the OrderForm
//UI window changes. This function updates the totals in the GUI based on the
//customer number selected
void OrderForm::on_custSelectSpin_valueChanged(int custNum)
{
    double total;
    //this will recalculate the order totals
    if(custNum == 0){
        //calculate total of entire bill
        total = ticket.calculateOrder();
    }
    else{
        //calculate total for selected customer - 1
        total = ticket.calculateOrder(custNum-1);
        //if customer number does not exist, update totals to zeros
        if (total == -1){
            calculateTotals(0);
            return;
        }
    }
    calculateTotals(total);
}

//This function is called anytime the test button is pressed in the OrderForm
//UI window. This function randomly generates menu items for an order ticket to facilitate testing
void OrderForm::on_testButton_clicked()
{
    //save the current values in MenuItemEdit and customer
    QString beforeItem = ui->MenuItemEdit->text();
    int beforeInt = ui->custSpin->value();

    //add a random amount of items to the order
    int foods[] = {101,102,103,104,105,201,202,203,204,205,401,402,403,404,405,501,502,503,504,
                   505,601,602,603,604,605,701,702,703,704,801,802,803,804,805,806};
    int foodSize = sizeof(foods)/sizeof(foods[0]);
    unsigned seed = time(0);
    srand(seed);
    int numOrders = rand()%8+3, customer = 1;
    for(int i = 0; i < numOrders; i++){
        QString item = QString::number(foods[rand()%foodSize]);
        ui->MenuItemEdit->setText(item);
        ui->custSpin->setValue(customer);
        on_AddItemButton_clicked();
        if(rand()%100<40){
            customer++;
        }
    }

    //restore the original values in MenuItemEdit and customer
    ui->MenuItemEdit->setText(beforeItem);
    ui->custSpin->setValue(beforeInt);
}

//This function is called when the user changes tabs in the OrderForm UI.
void OrderForm::on_OrderTabWidget_currentChanged(int index)
{
    //Order tab is selected
    if(index == 0){
        ui->RemoveItemButton->setText("Remove Selected Item");
        ui->AddItemButton->show();
    }
    //Menu tab is selected
    else if(index == 1){
        ui->RemoveItemButton->setText("Add Selected Item to Order");
        ui->AddItemButton->hide();
    }
}

/************************************************************************
 * setters and getters
 ************************************************************************/
//The functions in this section update or return hidden fields in the OrderForm
//UI that contain the values for the table and employee number for quick access
int OrderForm::getTableNum(){
    QString numStr = ui->tableNumLabel->text();
    int num = numStr.toInt();
    return num;
}

void OrderForm::setTableNum(int table){
    QString tableStr = QString::number(table);
    ui->tableNumLabel->setText(tableStr);
    ui->tableNumLabel->hide();
}

int OrderForm::getEmpNum(){
    QString numStr = ui->empNumLabel->text();
    int num = numStr.toInt();
    return num;
}

void OrderForm::setEmpNum(int empNum){
    FileSystem fs = FileSystem();
    Employee emp = fs.GetEmployee(empNum);
    ticket.setEmp(emp);
    QString empStr = QString::number(empNum);
    ui->empNumLabel->setText(empStr);
    ui->empNumLabel->hide();
}

/************************************************************************
 * other private methods
 ************************************************************************/

//This function updates the TableText field and the title, then shows the UI page
void OrderForm::showOrderPage(){
    int tableNo = getTableNum();
    QString tabletext = " Table #";
    tabletext += QString::number(tableNo);
    ui->TableText->setText(tabletext);
    QString title = "Order for" + tabletext;
    setWindowTitle(title);
    this->show();

}

//this function calculates the totals and updates the proper fields in the GUI
void OrderForm::calculateTotals(double subtotal){
    double taxed = subtotal * TAX;
    double totaled = subtotal + taxed;
    QString temp = "$" + QString::number(subtotal,'f',2);
    ui->SubtotalText->setText(temp);
    temp = "$" + QString::number(taxed,'f',2);
    ui->TaxText->setText(temp);
    temp = "$" + QString::number(totaled,'f',2);
    ui->GrantTotalText->setText(temp);
}

//this function cleans the UI and ticket object and reopens the login window
void OrderForm::closeOrder(){
    clearUI();
    ticket.cleanOrderTicket();
    calculateTotals(0);
    ui->listWidget->clear();
    endSession();
    this->hide();
}

//this function resets all the UI components
void OrderForm::clearUI(){
    ui->custSelectSpin->setValue(0);
    ui->custSpin->setValue(1);
    ui->quantSpin->setValue(1);
    QString empty = "";
    ui->MenuItemEdit->setText(empty);
}

//this function gets a ticket object from the order file via FS and builds
//the UI off of that object
void OrderForm::setupUI(int table){
    FileSystem fs = FileSystem();
    //create a temporary ticket object
    OrderTicket tempTicket;
    tempTicket = fs.GetOrderTicket(table);
    ticket.setOrderID(table);
    ticket.setTableNum(table);
    int cust = tempTicket.getOrderSize(), items;
    //build normal ticket and gui from contents of temp ticket
    for(int numCust = 0; numCust < cust; numCust++){
        items = tempTicket.getCustSize(numCust);
        for(int numItems = 0; numItems < items; numItems++){
            MenuItem temp = tempTicket.getItemAt(numCust, numItems);
            ui->MenuItemEdit->setText(QString::number(temp.getItemId()));
            ui->custSpin->setValue(numCust+1);
            on_AddItemButton_clicked();
        }
    }

    //clear UI values used by setup function
    ui->MenuItemEdit->setText("");
    ui->custSpin->setValue(1);

    //Add Employee name and number to UI
    Employee tempEmp = tempTicket.getEmp();
    Employee emp = ticket.getEmp();
    //if the emp object is the default employee, set it to tempEmp
    if(emp.getEmpNum() == 1234)
        emp = tempEmp;
    QString empInfo;
    //if the tempEmp object is not the default employee, and emp and tempEmp are
    //different, set the EmployeeLabel so that the order employee and logged in
    //employee are displayed, otherwise just display the employee
    if((tempEmp.getEmpNum() != 1234) &&
            (emp.getEmpNum() != tempEmp.getEmpNum())){
        ticket.setEmp(tempEmp);
        empInfo = QString::fromStdString(tempEmp.getEmpName()) + ", #"
                + QString::number(tempEmp.getEmpNum()) + " - Logged in as " +
                QString::fromStdString(emp.getEmpName()) + ", #"
                + QString::number(emp.getEmpNum());
    }else{
    empInfo = QString::fromStdString(emp.getEmpName()) + ", #"
            + QString::number(emp.getEmpNum());
    }
    ui->Employeelabel->setText(empInfo);

    //make sure that the order tab is selected
    ui->OrderTabWidget->setCurrentIndex(0);

    //setup Menu tab if it hasnt already been setup
    if(!menuSetup)
        setupMenu();
}

//this function sets up the Menu tab to make adding items easier
void OrderForm::setupMenu(){
    FileSystem fs = FileSystem();
    std::vector<MenuItem> menu = fs.GetAllMenuItems();
    int menuSize = menu.size();
    for(int i = 0; i < menuSize; i++){
        QString item = QString::fromStdString(menu[i].getItemDesc());
        new QListWidgetItem(item, ui->ItemListWidget, 0);
    }
    menuSetup = true;
}

//this function adds the selected item on the MenuOrder tab to the order
void OrderForm::addMenuItemToOrder(){
    //save the current text in MenuItemEdit
    QString before = ui->MenuItemEdit->text();

    //get the current item selected
    int row = ui->ItemListWidget->currentRow();
    //if there is no item selected, stop
    if(row==-1)
        return;
    QListWidgetItem * rem = ui->ItemListWidget->currentItem();
    QString item = rem->text();

    //add the item to the order
    ui->MenuItemEdit->setText(item);
    on_AddItemButton_clicked();

    //restore the original test in MenuItemEdit
    ui->MenuItemEdit->setText(before);
}

/************************************************************************
 * protected methods
 ************************************************************************/

//this function exists to try to allow the Enter key to activate a button
//it has not actually been implemented
bool OrderForm::eventFilter(QObject *obj, QEvent *event)
{
    if(event->type() == QEvent::KeyPress)
    {
        QKeyEvent *key = static_cast<QKeyEvent *>(event);

        if((key->key() == Qt::Key_Enter) || (key->key() == Qt::Key_Return))
        {
            //Enter or return was pressed
            on_AddItemButton_clicked();
        }
        else
        {
            return QObject::eventFilter(obj, event);
        }
        return true;
    }
    else
    {
        return QObject::eventFilter(obj, event);
    }

    return false;
}

//void OrderForm::keyPressEvent(QKeyEvent* pe)
//{
// if(pe->key() == Qt::Key_Return)
//     on_AddItemButton_clicked();
//  else
//     return QObject::eventFilter(obj, event);
//}

//these two functions exist for compatibilty with the FS class
void OrderTicket::setSeatNum(int seatNum){
   tableSeatNum = seatNum;
}

int OrderTicket::getSeatNum(){
   return tableSeatNum;
}
