#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "EmployeeSalary.h"
#include "../Entities/Entities.h"
// reporter


int main(int argc, char* argv[])
{
    const char* employeeFileName = argv[1];
    const char* reportFileName = argv[2];
    const char* hourSalaryChar = argv[3];

    double hourSalary = atoi(hourSalaryChar);


    std::ofstream reportFile(reportFileName);
    std::ifstream employeeFile(employeeFileName, std::ios::binary);

    reportFile << "Report from file " << employeeFileName << "\n"
        "ID\tNAME\t\HOURS\t\SALARY\n";

    Employee empl;
    std::vector<EmployeeSalary> emplSal;
    while (!employeeFile.read((char*)&empl, sizeof(Employee)).eof()) {
        emplSal.push_back({ empl, hourSalary * empl.hours });
        //reportFile << empl << "\t" << hourSalary * empl.hours << std::endl;
    }
    
    std::sort(emplSal.begin(), emplSal.end(), [](EmployeeSalary& s1, EmployeeSalary& s2) {
        return s1.salary > s2.salary;
    });

    for (auto i : emplSal) {
        reportFile << i << std::endl;
    }

    employeeFile.close();
    reportFile.close();

}