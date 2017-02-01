// Bradley Bales, bbbales@dmacc.edu
#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <string>

class Employee
{
private:
    int empNum;
    std::string empName;
    double empHours;

public:
/* constructors */
    Employee();
    Employee(int, std::string);
    ~Employee();
/* mutators */
    void setEmpNum(int);
    void setEmpName(std::string);
    void addHours(double);
    void setHours(double);
/* accessors */
    int getEmpNum();
    std::string getEmpName();
    int getHours();
};

#endif // EMPLOYEE_H
