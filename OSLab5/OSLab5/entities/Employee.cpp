#pragma once
#include <iostream>

using namespace std;

const int nameSize = 10;

struct Employee {
	int id;
	char name[nameSize];
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