// Brock Rikkers
#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <QDebug>
//#include <direct.h> //might not be used, windows specific
#include "OrderTicket.h"
#include "Employee.h"
#include "MenuItem.h"

class FileSystem
{
public:
	FileSystem();
	~FileSystem();
	void SaveOrderTicket(OrderTicket* o);
	void SaveEmployee(Employee* e);
    void AddMenuItems(std::vector<MenuItem>* items);
    void DeleteFile(std::string filename);
	bool IsValidMenuItem(std::string name);
    bool IsValidMenuItem(int id);
    MenuItem GetMenuItem(std::string name);
	OrderTicket GetOrderTicket(int order_id);
	Employee GetEmployee(int emp_id);
    MenuItem GetMenuItem(int item_id);
    bool FileExists(std::string filename);
    std::vector<MenuItem> GetAllMenuItems();
    void finalReceipt(OrderTicket* o);
};

