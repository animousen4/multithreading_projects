#pragma once

#include <Windows.h>
#include <iostream>
#include "../../entities/Command.cpp"
#include "../../entities/EmployeeResponse.cpp"
#include <string>
#include <fstream>
using namespace std;

struct ThreadArgs {
	HANDLE pipe;
	HANDLE fileMutex;
	string fileName;

	Employee* employees;
	int amount;
	
};

static EmployeeResponse getById(Employee* employees, int amount, int id) {
	for (int i = 0; i < amount; i++)
		if (id == employees[i].id)
			return { true, employees[i] };
	return { false, NULL };
}
static DWORD WINAPI threadFunc(LPVOID sId) {
	ThreadArgs args = *static_cast<ThreadArgs*>(sId);

	cout << "Created a thread for a pipe: " << args.pipe << endl;

	DWORD dwBytesRead;
	Command cm;
	while (true) {
		bool read = ReadFile(
			args.pipe,
			&cm, // to read
			sizeof(Command), // to read
			&dwBytesRead, // then read bytes
			(LPOVERLAPPED)NULL // sync
		);

		if (!read)
			break;

		if (cm.command[0] == 'r') {
			cout << "Reading from file..." << endl;
			cout << "Received command: " << cm.command << " " << cm.arg << endl;
			EmployeeResponse outEmpl = getById(args.employees, args.amount, cm.arg);
			DWORD dwBytesWrite;

			WriteFile(
				args.pipe,
				(char*)&outEmpl, // to out
				sizeof(EmployeeResponse), // to write Bytes
				&dwBytesWrite, // then written bytes
				(LPOVERLAPPED)NULL // sync
			);

		}
		else if (cm.command[0] == 'm') {

			EmployeeResponse outEmpl = getById(args.employees, args.amount, cm.arg);
			DWORD dwBytesWrite;

			WriteFile(
				args.pipe,
				(char*)&outEmpl, // to out
				sizeof(EmployeeResponse), // to write Bytes
				&dwBytesWrite, // then written bytes
				(LPOVERLAPPED)NULL // sync
			);

			if (outEmpl.ok) {
				Employee toReadModifiedEmpl;
				bool read = ReadFile(
					args.pipe,
					(char*)&toReadModifiedEmpl, // to read
					sizeof(Employee), // to read
					&dwBytesRead, // then read bytes
					(LPOVERLAPPED)NULL // sync
				);

				cout << "Received modified employee: " << toReadModifiedEmpl;

				WaitForSingleObject(args.fileMutex, INFINITE);
				{
					cout << "Modifying in file...";
					//ofsteam

				}
				ReleaseMutex(args.fileMutex);
				
			}
			else {
				cout << "No such employee, nothing to modify";
			}
		}
		else {
			cout << "Unsupported command" << endl;
		}
	}

	cout << "Thread finished" << endl;

	return 0;
}