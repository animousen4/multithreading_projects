#pragma once

#include "Employee.cpp";
struct EmployeeResponse {
	bool ok;
	Employee empl;

	friend istream& operator>> (istream& stream, EmployeeResponse& empl) {
		stream >> empl.ok >> empl.empl;
		return stream;
	}

	friend ostream& operator<< (ostream& stream, EmployeeResponse& empl) {
		stream << empl.ok << empl.empl;
		return stream;
	}
};