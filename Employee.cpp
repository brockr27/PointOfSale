// Bradley Bales, bbbales@dmacc.edu
#include "Employee.h"

/* constructors */
Employee::Employee(){
empNum = 1234;
empName = "Default Employee";
empHours = 0;
}

Employee::Employee(int num, std::string name){
empNum = num;
empName = name;
empHours = 0;
}

Employee::~Employee(){

}

/* mutators */
void Employee::setEmpNum(int num){
empNum = num;
}

void Employee::setEmpName(std::string name){
empName = name;
}

void Employee::addHours(double hours){
empHours += hours;
}

void Employee::setHours(double hours){
empHours = hours;
}


/* accessors */
int Employee::getEmpNum(){
return empNum;
}

std::string Employee::getEmpName(){
return empName;
}

int Employee::getHours(){
return empHours;
}
