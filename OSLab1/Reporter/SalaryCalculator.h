#pragma once
#include "EmployeeSalary.h"
#include "NegativeNumberException.h"
class SalaryCalculator {
public:
	EmployeeSalary calculateSalary(Employee empl, double hourSalary) {
		double res = hourSalary * empl.hours;
		if (res < 0)
			throw std::runtime_error("Should be > 0");
		return EmployeeSalary{ empl, hourSalary * empl.hours };
	}
};