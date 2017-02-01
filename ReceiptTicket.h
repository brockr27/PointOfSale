#ifndef RECEIPTTICKET_H
#define RECEIPTTICKET_H

#include <string>
#include "Employee.h"
#include "MenuItem.h"
#include "OrderTicket.h"

class ReceiptTicket
{
private:
    int order_id, empNum, tableNum, item_id, itemQuantity;
    std::string item_desc;
    double item_price;
    //Replace the above variables with an OrderTicket object?
    //have a customer variable to allow the ReceiptTicket to only calculate the cust's item totals
    int cust;
    double receiptSubTotal, discounts, tax, receiptTotal;

    void calculateOrderTotals();

public:
/* constructors */
    ReceiptTicket();
    ReceiptTicket(OrderTicket);
    ~ReceiptTicket();
/* mutators */
/* accessors */
    //can call the same functions from the OrderTicket
    int getOrderID();
    Employee getEmp();
    int getTableNum();
    //might need to make sure calculateOrderTotals is run before these functions run
    double getSubTotal();
    double getTax();
    double getGrandTotal();
    double getDiscountPercent();

};

#endif // RECEIPTTICKET_H
