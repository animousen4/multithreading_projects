#include <windows.h>
#include <iostream>
#include <fstream>
#include "../entities/Employee.cpp";
#include "process/process_manager.h"
#include "../entities/Command.cpp"
#include "../entities/EmployeeResponse.cpp"
#include "thread/thread_func.cpp"
#include "thread/thread_manager.h"
using namespace std;

int main()
{	

	string fileName;
	int studentAmount;
	int clientAmount;
	Employee* employees;
	ProcessManager* processManagers;
	ThreadManager* threadManagers;
	HANDLE* threads;
	ThreadArgs* threadArgs;

	HANDLE fileMutex = OpenMutexA(MUTEX_ALL_ACCESS, TRUE, NULL);

	cout << "fileName: ";
	cin >> fileName;
	cout << "studentAmount: ";
	cin >> studentAmount;

	cout << "clientsAmount: ";
	cin >> clientAmount;

	employees = new Employee[studentAmount];
	processManagers = new ProcessManager[clientAmount];
	threadManagers = new ThreadManager[clientAmount];
	threadArgs = new ThreadArgs[clientAmount];
	threads = new HANDLE[clientAmount];

	cout << "id\tname\thours" << endl;
	for (int i = 0; i < studentAmount; i++)
		cin >> employees[i];


	// creating bin file
		
	ofstream binFile(fileName, ios::binary);
	for (int i = 0; i < studentAmount; i++) {
		binFile.write((char*)(&employees[i]), sizeof(Employee));
	}

	binFile.close();
	
	HANDLE hNamedPipe;

	for (int i = 0; i < clientAmount; i++) {

		hNamedPipe = CreateNamedPipe(
			"\\\\.\\pipe\\demo_pipe",
			PIPE_ACCESS_DUPLEX, // READ AND WRITE
			PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT, // sync
			PIPE_UNLIMITED_INSTANCES, // amount of channels
			0, // 
			0, // 
			INFINITE, // inf
			(LPSECURITY_ATTRIBUTES)NULL
		);


		processManagers[i].createApp("Client.exe");
		threadArgs[i] = ThreadArgs{ hNamedPipe, fileMutex, fileName, employees, studentAmount, i + 1};
		
		cout << "Waiting client #" << i + 1 << " ... ";
		bool res = ConnectNamedPipe(
			hNamedPipe,
			(LPOVERLAPPED)NULL // sync
		);
		threads[i] = threadManagers[i].createThread(threadFunc, (LPVOID)&threadArgs[i]);

		if (res)
			cout << "Connection SUCCESS" << endl;
		else
			cout << "Connection FAILED; Error: " << GetLastError() << endl;
	}
	cout << "[SERVER] " << endl;
	WaitForMultipleObjects(clientAmount, threads, TRUE, INFINITE);

	return 0;
	

	

	

	
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

	
	

	
	



	CloseHandle(hNamedPipe);

	return 0;
}