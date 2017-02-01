//Written by Mark Lee
//Edited by Bradley Bales
#ifndef MENUITEM_H
#define MENUITEM_H

#include <string>

class MenuItem
{
private:
    int item_id;
    std::string item_desc;
    double item_price;

public:
/* constructors */
    MenuItem();
    MenuItem(int, double, std::string);
    ~MenuItem();
/* mutators */
    void setItemId(int);
    void setItemDesc(std::string);
    void setItemPrice(double);
/* accessors */
    int getItemId();
    std::string getItemDesc();
    double getItemPrice();
    void createItem(int, double, std::string);
};

#endif // MENUITEM_H
