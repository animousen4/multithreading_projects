#include <windows.h>
#include <iostream>
#include <fstream>
#include "../entities/Employee.cpp";
#include "process/process_manager.h"
#include "../entities/Command.cpp"
using namespace std;


Employee getById(Employee* employees, int amount, int id, bool& ok) {
	ok = true;
	for (int i = 0; i < amount; i++)
		if (id == employees[i].id)
			return employees[i];
	ok = false;
	return Employee();
}
int main()
{	

	string fileName;
	int studentAmount;
	int clientAmount;
	Employee* employees;
	ProcessManager* managers;

	cout << "fileName: ";
	cin >> fileName;
	cout << "studentAmount: ";
	cin >> studentAmount;

	cout << "clientsAmount: ";
	cin >> clientAmount;

	employees = new Employee[studentAmount];
	managers = new ProcessManager[clientAmount];

	cout << "id\tname\thours" << endl;
	for (int i = 0; i < studentAmount; i++)
		cin >> employees[i];

	if (studentAmount >= 0) {
		// creating bin file
		
		ofstream binFile(fileName, ios::binary);
		for (int i = 0; i < studentAmount; i++) {
			binFile.write((char*)(&employees[i]), sizeof(Employee));
		}

		binFile.close();
	}
	else {
		cout << "Students amount is negative, using old file" << endl;
	}


	for (int i = 0; i < clientAmount; i++)
		managers[i].createApp("Client.exe");
	/*
 
	ifstream binFileOpen(fileName, ios::binary);
	Employee empl;
	for (int i = 0; i < studentAmount; i++) {
		binFileOpen.read((char*)(&empl), sizeof(Employee));
		cout << empl << endl;
	}

	binFileOpen.close();
	
	*/

	//return 0;

	char c;
	HANDLE hNamedPipe;
	hNamedPipe = CreateNamedPipe(
		"\\\\.\\pipe\\demo_pipe",
		PIPE_ACCESS_DUPLEX, // READ AND WRITE
		PIPE_TYPE_MESSAGE | PIPE_WAIT, // sync
		1, // amount of channels
		0, // 
		0, // 
		INFINITE, // inf
		(LPSECURITY_ATTRIBUTES)NULL
	);
	if (hNamedPipe == INVALID_HANDLE_VALUE)
	{
		cerr << "Creation of the named pipe failed." << endl
			<< "The last error code: " << GetLastError() << endl;
		cout << "Press any char to finish server: ";
		cin >> c;
		return 0;
	}

	cout << "The server is waiting for connection with a client." << endl;
	if (!ConnectNamedPipe(
		hNamedPipe,
		(LPOVERLAPPED)NULL // sync
	))
	{
		cerr << "The connection failed." << endl << "The last error code: " << GetLastError() << endl;

		CloseHandle(hNamedPipe);
		cout << "Press any char to finish the server: ";
		cin >> c;
		return 0;
	}

	DWORD dwBytesRead;
	Command cm;
	
	ReadFile(
		hNamedPipe,
		&cm, // to read
		sizeof(Command), // to read
		&dwBytesRead, // then read bytes
		(LPOVERLAPPED)NULL // sync
	);

	if (cm.command[0] == 'r') {
		Employee outEmpl;
		DWORD dwBytesWrite;
		WriteFile(
			hNamedPipe,
			(char*)&outEmpl, // to out
			sizeof(Employee), // to write Bytes
			&dwBytesWrite, // then written bytes
			(LPOVERLAPPED)NULL // sync
		);
	}



	CloseHandle(hNamedPipe);

	return 0;
}