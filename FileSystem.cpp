/* Brock Rikkers
 Creates a fileSystem object, which you can then use to feed in OrderTickets,
 Employees, or a menuItems vector to save into a notepad file.
 You can also use it to read in those files and return their respective objects.
 The files are usually located in your user folder (ie. C:\Users\YOURNAME\ )
*/
#include "FileSystem.h"

using std::string;
using std::stringstream;
using std::ofstream;
using std::ifstream;
using std::to_string;

FileSystem::FileSystem()
{
}

FileSystem::~FileSystem()
{
}

void FileSystem::SaveOrderTicket(OrderTicket* o)
{
    string wholePath = "Order" + to_string(o->getOrderId()) + ".txt";
    DeleteFile(wholePath);
    ofstream myfile;

	try {
		myfile.open(wholePath);
	}
    catch(int e) {
        qDebug() << "An error occured opening the file: " << QString::fromStdString(wholePath) << "!" << e;
		return;
	}
	
	// Writes the order header info all on one line, seperated by commas
    myfile << o->getOrderId() << "," << o->getEmpNum() << "," << o->getTableNum()
        << "," << o->getSeatNum() << "," << o->getOrderTime() << "\n";

	// Goes through the orders
	for(int unsigned cust = 0; cust < o->getOrderSize(); cust++)
	{
		// Writes the customer's id
        myfile << (cust + 1) << "," << o->getCustSize(cust) << "\n";

		// Goes through the customer's items
		for(int unsigned item = 0; item < o->getCustSize(cust); item++)
		{
			MenuItem temp = o->getItemAt(cust, item);
            myfile << temp.getItemId() << "\n";
		}
    }

	myfile.close();
}

OrderTicket FileSystem::GetOrderTicket(int order_id)
{
    string wholePath = "Order" + to_string(order_id) + ".txt";
    ifstream myFile;
    OrderTicket ord = OrderTicket();

    //return OrderTicket object if file does not exist
    if(!FileExists(wholePath)){
        qDebug() << "File Does Not Exist";
        return ord;
    }

	try {
		myFile.open(wholePath);
	}
	catch(int e) {
        qDebug() << "An error occured opening the file: " << QString::fromStdString(wholePath) << "!" << e << endl;
		return OrderTicket();
    }

	int count = 0;
    int data[100];
    string s;
    string s2;
	int pos = 0;

	// Get each line in the file and put it into s;
	while(getline(myFile, s).eof() == false)
	{
		// Break up s by the delimeter ',' and put the values into data[]
		while((pos = s.find(",")) != s.npos) {
			s2 = s.substr(0, pos);
			data[count] = atoi(s2.c_str());
			count++;
			s.erase(0, pos + 1);		// erases the used substring so we can start at 0 with the line "s2 = s.substr(0, pos)" to make it easier
		}
		// Adding in the last number, otherwise it wont get it due to how delimeters work
		s2 = s.substr(0, pos);
		data[count] = atoi(s2.c_str());
		count++;
	}
	
    Employee e = GetEmployee(data[1]);
	ord.setOrderID(order_id);
    ord.setEmp(e);
	ord.setTableNum(data[2]);
	ord.setSeatNum(data[3]);
	ord.setOrderTime(data[4]);
	
	// Set to 5 because its where the actual orders start, the while loop will go through every element of data[]
	int i = 5;
	while(i < count)
	{
		int custID = data[i++];
		int numOrders = data[i++];
		// For each customer, make sure to get every order
		for(int j = 0; j < numOrders; j++)
		{
			MenuItem mi = GetMenuItem(data[i++]);
			ord.addItemToOrder(custID, mi);
		}
	}

	return ord;
}

void FileSystem::AddMenuItems(std::vector<MenuItem>* items)
{
    ofstream myFile;
    string filename = "MenuItems.txt";
	try {
        myFile.open(filename);
	}
	catch(int e) {
        qDebug() << "An error occured opening the file: MenuItems.txt" << "!" << e << endl;
		return;
	}

	for(int i = 0; i < items->size(); i++) {
		MenuItem mi = items->at(i);
        myFile << mi.getItemId() << "," << mi.getItemPrice() << "," << mi.getItemDesc()<< "\n";
	}

	myFile.close();
}

bool FileSystem::IsValidMenuItem(string name) {
    ifstream myFile;
    try {
        myFile.open("MenuItems.txt");
    }
    catch(int e) {
        qDebug() << "An error occured opening the file: MenuItems.txt!" << e;
        return false;
    }

    int count = 0;
    string data[3];
    string s;
    string s2;
    int pos = 0;

    // Get each line in the file and put it into s;
    while(getline(myFile, s).eof() == false)
    {
        count = 0;
        // Break up s by the delimeter ',' and put the values into data[]
        while((pos = s.find(",")) != s.npos) {
            s2 = s.substr(0, pos);
            data[count] = s2;
            count++;
            s.erase(0, pos + 1);		// erases the used substring so we can start at 0 with the line "s2 = s.substr(0, pos)" to make it easier
        }
        // Adding in the last number, otherwise it wont get it due to how delimeters work
        s2 = s.substr(0, pos);
        data[count] = s2;
        count++;

        // Converting both strings to lower case so I can compare them
        std::transform(data[2].begin(), data[2].end(), data[2].begin(), ::tolower);
        std::transform(name.begin(), name.end(), name.begin(), ::tolower);

        if(data[2] == name) {
            myFile.close();
            return true;
        }
    }

    myFile.close();
    return false;
}

//direct clone of the string version, modified for ints by David
bool FileSystem::IsValidMenuItem(int id) {
    ifstream myFile;
    try {
        myFile.open("MenuItems.txt");
    }
    catch(int e) {
        qDebug() << "An error occured opening the file: MenuItems.txt!" << e;
        return false;
    }

    int count = 0;
    string data[3];
    string s;
    string s2;
    int pos = 0;

    // Get each line in the file and put it into s;
    while(getline(myFile, s).eof() == false)
    {
        count = 0;
        // Break up s by the delimeter ',' and put the values into data[]
        while((pos = s.find(",")) != s.npos) {
            s2 = s.substr(0, pos);
            data[count] = s2;
            count++;
            s.erase(0, pos + 1);		// erases the used substring so we can start at 0 with the line "s2 = s.substr(0, pos)" to make it easier
        }
        // Adding in the last number, otherwise it wont get it due to how delimeters work
        s2 = s.substr(0, pos);
        data[count] = s2;
        count++;

        // Converting both strings to lower case so I can compare them
//        std::transform(data[2].begin(), data[2].end(), data[2].begin(), ::tolower);
//        std::transform(name.begin(), name.end(), name.begin(), ::tolower);

        if(std::stoi(data[0].c_str()) == id) {
            myFile.close();
            return true;
        }
    }

    myFile.close();
    return false;
}

MenuItem FileSystem::GetMenuItem(string name) {
    if(!IsValidMenuItem(name))
        return MenuItem();
    MenuItem item = MenuItem();
    ifstream myFile;
    try {
        myFile.open("MenuItems.txt");
    }
    catch(int e) {
        qDebug() << "An error occured opening the file: MenuItems.txt!" << e;
        return item;
    }

    int count = 0;
    string data[3];
    string s;
    string s2;
    int pos = 0;

    // Get each line in the file and put it into s;
    while(getline(myFile, s).eof() == false)
    {
        count = 0;
        // Break up s by the delimeter ',' and put the values into data[]
        while((pos = s.find(",")) != s.npos) {
            s2 = s.substr(0, pos);
            data[count] = s2;
            count++;
            s.erase(0, pos + 1);		// erases the used substring so we can start at 0 with the line "s2 = s.substr(0, pos)" to make it easier
        }
        // Adding in the last number, otherwise it wont get it due to how delimeters work
        s2 = s.substr(0, pos);
        data[count] = s2;
        count++;

        // Converting both strings to lower case so I can compare them
        std::transform(data[2].begin(), data[2].end(), data[2].begin(), ::tolower);
        std::transform(name.begin(), name.end(), name.begin(), ::tolower);

        if(data[2] == name) {
            myFile.close();
            item.setItemId(std::stoi(data[0].c_str()));
            // for some reason, the precision is slightly off for the price (ie. 6.99 becomes 6.99000000002). No idea how to fix, floor() doesn't work
            item.setItemPrice(std::stod(data[1].c_str()));
            item.setItemDesc(data[2]);
            return item;
        }
    }

    myFile.close();
    return item;
}

MenuItem FileSystem::GetMenuItem(int item_id) {
    ifstream myFile;
    try {
        myFile.open("MenuItems.txt");
    }
    catch(int e) {
        qDebug() << "An error occured opening the file: MenuItems.txt" << "!" << e << endl;
        return MenuItem();
    }

    int count;
    string data[3];
    string line;
    bool wasFound = false;

    // Get the entire line
    while(getline(myFile, line).good() && wasFound == false)
    {
        data[0] = "";
        data[1] = "";
        data[2] = "";
        count = 0;

        // Split the line into the data[] array using commas as delimeters
        stringstream ss(line);
        string s;
        while(getline(ss, s, ',').good() && count < 3) {
            data[count++] = s;
        }
        // Adding in the last number, otherwise it wont get it due to how delimeters work
        data[count] = s;

        // If the item was found, set the bool to true
        if(atoi(data[0].c_str()) == item_id)
            wasFound = true;
    }

    // If we make a constructor with parameters, this can be changed to make it easier to read.
    MenuItem m = MenuItem();
    m.setItemId(item_id);
    m.setItemPrice(stod(data[1]));
    m.setItemDesc(data[2]);

    myFile.close();
    return m;
}

void FileSystem::SaveEmployee(Employee* e)
{
    double hours;
	if(e->getHours() <= 0)
		hours = 0;
	else
		hours = e->getHours();

    string wholePath = string("Employee" + to_string(e->getEmpNum()) + ".txt");
    ofstream myFile;
	try {
		myFile.open(wholePath);
	}
	catch(int e) {
        qDebug() << "An error occured opening the file: " << QString::fromStdString(wholePath) << "!" << e << endl;
	}

	myFile << e->getEmpNum() << "," << e->getEmpName() << "," << hours << endl;

	myFile.close();
}

Employee FileSystem::GetEmployee(int emp_id)
{
    string wholePath = string("Employee" + to_string(emp_id) + ".txt");
    ifstream myFile;
    Employee e = Employee();

    //return Employee object if file does not exist
    if(!FileExists(wholePath)){
        qDebug() << "File Does Not Exist";
        return e;
    }

	try {
		myFile.open(wholePath);
	}
	catch(int e) {
        qDebug() << "An error occured opening the file: " << QString::fromStdString(wholePath) << "!" << e << endl;
		return Employee();
	}

	int count = 0;
    string data[3];
    string s;

	while(getline(myFile, s, ',').good() && count < 3)
	{
		data[count] = s;
		count++;
	}
	// Adding in the last number, otherwise it wont get it due to how delimeters work
	data[count] = s;

	// If we make a constructor with parameters, this can be changed to make it easier to read.
	e.setEmpNum(emp_id);
	e.setEmpName(data[1]);
	e.setHours(stod(data[2]));

	return e;
}

void FileSystem::DeleteFile(string filename) {
    if(!FileExists(filename))
        return;
    const char* name = filename.c_str();
    if(remove(name) != 0)
        perror("Error deleting file");
}

//this function takes in a string filename and returns a bool on whether or not the file exists, written by David
bool FileSystem::FileExists(string filename){
    ifstream myFile;

    //attempt
    try {
        myFile.open(filename);
    }
    catch(int e) {
        qDebug() << "An error occured opening the file: " << QString::fromStdString(filename) << "!" << e << endl;
        return false;
    }

    //return OrderTicket object if file does not exist
    if(!myFile){
        myFile.close();
        return false;
    }else{
        myFile.close();
        return true;
    }
}

//function copied from MenuItem int fucntion, returns a vector of MenuItems. Edited by David
std::vector<MenuItem> FileSystem::GetAllMenuItems() {
    ifstream myFile;
    std::vector<MenuItem> ret;
    try {
        myFile.open("MenuItems.txt");
    }
    catch(int e) {
        qDebug() << "An error occured opening the file: MenuItems.txt" << "!" << e << endl;
        return ret;
    }

    int count;
    string data[3];
    string line;

    // Get the entire line
    while(getline(myFile, line).good())
    {
        data[0] = "";
        data[1] = "";
        data[2] = "";
        count = 0;

        // Split the line into the data[] array using commas as delimeters
        stringstream ss(line);
        string s;
        while(getline(ss, s, ',').good() && count < 3) {
            data[count++] = s;
        }
        // Adding in the last number, otherwise it wont get it due to how delimeters work
        data[count] = s;

        MenuItem m = MenuItem();
        m.setItemId(stoi(data[0]));
        m.setItemPrice(stod(data[1]));
        m.setItemDesc(data[2]);
        ret.push_back(m);
    }

    myFile.close();
    return ret;
}

void FileSystem::finalReceipt(OrderTicket* o){

   double totalVar = o->calculateOrder();

    string date = "12/8/2014";//to be edited

    int item = 3;
    double item_price = 0.00;
    double total_item = item*item_price;
    double tax_total = 0.07 *total_item;

   // ReceiptTicket rs = ReceiptTicket();
   // double subT = rs.ReceiptTicket(getSubTotal);

    string writeCurrent = "ReceiptFinal" + to_string(o->getOrderId()) + ".txt";
    DeleteFile(writeCurrent);

    string orderReceiptNum = to_string(o->getOrderId());

    ofstream writeCurrentReceipt;

    //edwin
    try {
        writeCurrentReceipt.open(writeCurrent);
    }
    catch(int e) {
         qDebug() << "An error occured opening the file: " << QString::fromStdString(writeCurrent) << "!" << e;
           return;
    }


    //open file read file
    //std::string; writeCurrent.open("receipt_History.dat", std::ios_base::app);

    //write in date receipt_History.dat

    writeCurrentReceipt << "________________________________________________________\n";
    writeCurrentReceipt << "Receipt Invoice - " << orderReceiptNum << "          Server: " << o->getEmp().getEmpName() << "              "  <<"\n";
    writeCurrentReceipt << "--------------------------------------------------------" <<"\n";
    writeCurrentReceipt << "Items           " << "                           " << "Price" <<"\n";

    for(int cust = 0; cust < o->getOrderSize(); cust++){
        for(int item = 0; item < o->getCustSize(cust); item++){
            writeCurrentReceipt<<o->getItemAt(cust, item).getItemDesc() << "                        "  << "$ "<< o->getItemAt(cust, item).getItemPrice() <<"\n";
        }
    }



    //while(!receiptCallnow.eof){
      //   writeCurrentReceipt<<receiptCallnow<< "                        " <<item_price << "$ "<< total_item <<"\n";
    // }

    double subtotal = o->calculateOrder();
    writeCurrentReceipt<<"                                \n";
    writeCurrentReceipt << "--------------------------------------------------------" <<"\n";
    writeCurrentReceipt << "                                   Subtotal : $ " << subtotal  <<"\n";
    writeCurrentReceipt << "                                     6% tax : $ " << subtotal * .06<<"\n";
    writeCurrentReceipt << "--------------------------------------------------------" <<"\n";
    writeCurrentReceipt << "                                Final Total : $ " << subtotal * 1.06 <<"\n";
    writeCurrentReceipt << "________________________________________________________" <<"\n";

    //close file
    writeCurrentReceipt.close();

}
