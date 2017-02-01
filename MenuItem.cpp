//Written by Mark Lee
//Edited by Bradley Bales
#include "MenuItem.h"

MenuItem::MenuItem(){
    item_id = 0;
    item_desc = "default item";
    item_price = 0.0;
}

MenuItem::MenuItem(int id, double price, std::string desc)
{
    item_id = id;
    item_price = price;
    item_desc = desc;
}

MenuItem::~MenuItem(){

}

/* mutators */
void MenuItem::setItemId(int id)
{
    item_id = id;
}

void MenuItem::setItemDesc(std::string desc)
{
    item_desc = desc;
}

void MenuItem::setItemPrice(double price)
{
    item_price = price;
}


/* accessors */
void MenuItem::createItem(int id, double price, std::string desc)
{
    item_id = id;
    item_price = price;
    item_desc = desc;
}

int MenuItem::getItemId()
{
    return item_id;
}
std::string MenuItem::getItemDesc()
{
    return item_desc;
}
double MenuItem::getItemPrice()
{
    return item_price;
}
