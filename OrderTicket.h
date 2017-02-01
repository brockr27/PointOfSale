//written by David De Leon
#ifndef ORDERTICKET_H
#define ORDERTICKET_H

#include <string>
#include <vector>
#include <QDebug>
#include "Employee.h"
#include "MenuItem.h"

typedef std::vector< std::vector<MenuItem> > MIvect;

class OrderTicket
{
private:
    int tableSeatNum, item_id;
    std::vector<int> counts;
    int order_id, tableNum;
    double order_Time_In;
    //this vector translates to customer<MenuItem<quantity>>>
//    std::vector< std::vector< std::vector<MenuItem> > > order;
    MIvect order;
    Employee emp;


public:
/* constructors */
    OrderTicket();
    ~OrderTicket();
/* mutators */
    void setOrderID(int);
    void setEmpNum(int);
    void setEmp(Employee);
    void setTableNum(int);
    void setSeatNum(int);
    void setItemDesc(std::string);
    void setOrderTime(double);
/* accessors */
    int getOrderId();
    int getEmpNum();
    Employee getEmp();
    int getTableNum();
    int getSeatNum();
    int getItemId(int cust, int orderIndex);
    int getQuantity(int cust, int indexID);
    std::string getItemDesc();
    double getOrderTime();
/* other member functions */
    void addItemToOrder(int cust, MenuItem item);
    void removeItem(int cust, int itemId);
    double calculateOrder();
    double calculateOrder(int cust);
    MenuItem getItemAt(int cust, int itemIndex);
    void cleanOrderTicket();
    int getOrderSize();
    int getCustSize(int cust);
};

#endif // ORDERTICKET_H
