#pragma once
#include "../Entities/Entities.h"

struct EmployeeSalary {
    Employee empl;
    double salary;

    friend std::ostream& operator<<(std::ostream& s, const EmployeeSalary& e) {
        s << e.empl << "\t" << e.salary;
        return s;
    }
};