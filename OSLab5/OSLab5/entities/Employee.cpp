#pragma once
#include <iostream>

using namespace std;

struct Employee {
	int id;
	char name[10];
	double hours;

	friend istream& operator>> (istream& stream, Employee& empl) {
		stream >> empl.id >> empl.name >> empl.hours;
		return stream;
	}

	friend ostream& operator<< (ostream& stream, Employee& empl) {
		stream << empl.id << empl.name << empl.hours;
		return stream;
	}
};