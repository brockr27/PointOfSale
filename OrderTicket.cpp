/*written by David De Leon
 * This class represents the order for a given table.
*/
#include "OrderTicket.h"

/************************************************************************
 * constructors *
 ************************************************************************/
OrderTicket::OrderTicket(){
    std::vector<MenuItem> temp;
    order.push_back(temp);
    tableSeatNum = 0;
    counts.push_back(0);
}

OrderTicket::~OrderTicket(){
}

/************************************************************************
 * mutators *
 ************************************************************************/
//sets the order_id to the int idNum
void OrderTicket::setOrderID(int idNum){
    order_id = idNum;
}

//sets the employee object to the Employee object e passed to the function
void OrderTicket::setEmp(Employee e){
    emp = e;
}

//sets the table number to the int num
void OrderTicket::setTableNum(int num){
    tableNum = num;
}

//sets the time of the order to the double time
void OrderTicket::setOrderTime(double time){
    order_Time_In = time;
}

/************************************************************************
 * accessors *
 ************************************************************************/
//returns the order ID
int OrderTicket::getOrderId(){
    return order_id;
}

//returns the employee number from the Employee object
int OrderTicket::getEmpNum(){
    return emp.getEmpNum();
}

//returns the Employee object
Employee OrderTicket::getEmp(){
    return emp;
}

//returns the table number
int OrderTicket::getTableNum(){
    return tableNum;
}

//returns the order time
double OrderTicket::getOrderTime(){
    return order_Time_In;
}

/************************************************************************
 * other member functions *
 ************************************************************************/
//adds the MenuItem to the order for cust
void OrderTicket::addItemToOrder(int cust, MenuItem item){
    //UI starts at 1, decrement customer number after being recieved
    cust--;
    bool pushed = false;
    while(!pushed){
        //if the customer already exists in the ticket, add the item
        if(cust < order.size()){
            order[cust].push_back(item);
            pushed = true;
            counts[cust]++;
//             qDebug() << "counts[" << cust << "]=" << counts[cust];
        //else create new customers until number of customers is reached
        }else{
            std::vector<MenuItem> temp;
            order.push_back(temp);
            counts.push_back(0);
        }
    }
}

//removes the item itemId from the order for custArg
void OrderTicket::removeItem(int custArg, int itemId){
//remove the menu item from order[cust] vector
//need to search the id to find the item to remove
    int cust = custArg-1;
    if(cust <= order.size()){
        //search through the array, when itemId is found, move all subsequent items forward and remove the last item
        for(int i = 0; i <order[cust].size(); i++){
            int currItem = order[cust][i].getItemId();
            if (currItem == itemId){
                for(int j = i+1; j<=order[cust].size()-1; j++, i++){
                    order[cust][i] = order[cust][j];
                }
                order[cust].pop_back();
                counts[cust]--;
                break;
            }
        }
    }
    int placeholder;
    placeholder = 0;
}

//this function returns a double value for the entire value of the order
double OrderTicket::calculateOrder(){
    double total = 0.0;
    int debug_count = 0;
    for(int unsigned cust = 0; cust < order.size(); cust++){
        for(int unsigned item = 0; item < order[cust].size(); item++){
            MenuItem temp = order[cust][item];
            total += temp.getItemPrice();
            debug_count++;
        }
    }
    return total;
}

//this function returns a double value for the value of the order for cust
double OrderTicket::calculateOrder(int cust){
    if(cust >= order.size())
        return -1;
    double total = 0.0;
    for(int unsigned item = 0; item < order[cust].size(); item++){
        MenuItem temp = order[cust][item];
        total += temp.getItemPrice();
    }

    return total;
}

//return the MenuItem from the order for cust at itemIndex
MenuItem OrderTicket::getItemAt(int cust, int itemIndex){
    if(cust < order.size()){
        if(itemIndex < order[cust].size())
            return order[cust][itemIndex];
    }
}

//this function resets various variables so the object can be reused
void OrderTicket::cleanOrderTicket(){
    int numCust = order.size();
    for(int i = 0; i < numCust; i++){
        order.pop_back();
    }
    int countSize = counts.size();
    for(int i = 0; i < countSize; i++){
        counts.pop_back();
    }
    counts.push_back(0);
    std::vector<MenuItem> temp;
    order.push_back(temp);
}

//return the number of customers
int OrderTicket::getOrderSize(){
    return counts.size();
}

//return the number of items in the order for cust
int OrderTicket::getCustSize(int cust){
    return counts[cust];
}
