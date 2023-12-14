#include <windows.h>
#include <iostream>
#include <string>
#include <fstream>
#include "../entities/Employee.cpp";
#include "../entities/Command.cpp"
#include "../entities/EmployeeResponse.cpp"
#include "../common/pipename.cpp"
using namespace std;


int main()
{	
	cout << "[Client]" << endl;
	HANDLE hNamedPipe;
	HANDLE fileMutex = OpenMutexA(MUTEX_ALL_ACCESS, TRUE, "fileMutex");

	if (!WaitNamedPipe(TEXT(connectionPipeName), NMPWAIT_WAIT_FOREVER)) {
		printf("Error waiting for named pipe\n");
		return 1;
	}

	hNamedPipe = CreateFileA(
		connectionPipeName,
		GENERIC_READ | GENERIC_WRITE, // write and read
		FILE_SHARE_READ, // read
		(LPSECURITY_ATTRIBUTES)NULL,
		OPEN_EXISTING, // open exist
		0, 
		(HANDLE)NULL
	);
	// check connect
	if (hNamedPipe == INVALID_HANDLE_VALUE)
	{
		cerr << "Connection with the named pipe failed." << endl
			<< "The last error code: " << GetLastError() << endl;
		system("pause");

		return 0;
	}
	// write to channel
	DWORD dwBytesWritten;
	DWORD dwBytesRead;
	Command cm;
	EmployeeResponse resp;
	bool read;
	while (true) {
		cin >> cm.command >> cm.arg;
		if (cm.command[0] == 'r' || cm.command[0] == 'm') {
			WriteFile(
				hNamedPipe,
				(char*)&cm, // data
				sizeof(Command), // data size
				&dwBytesWritten, // written
				(LPOVERLAPPED)NULL // sync
			);

			read = ReadFile(
				hNamedPipe,
				&resp, // to read
				sizeof(EmployeeResponse), // to read
				&dwBytesRead, // then read bytes
				(LPOVERLAPPED)NULL // sync
			);

			if (!read)
				break;

			if (resp.ok) {
				cout << resp.empl.id << " " << resp.empl.name << " " << resp.empl.hours << endl;
				
				if (cm.command[0] == 'm') {
					WaitForSingleObject(fileMutex, INFINITE);

					Employee newEmpl;
					bool validated = false;

					while (!validated) {
						cout << "Enter the changes:" << endl;
						cout << "name\thours" << endl;
						newEmpl.id = cm.arg;
						string name;
						cin >> name >> newEmpl.hours;

						if (name.length() < nameSize) {
							validated = true;
							strcpy(newEmpl.name, name.c_str());
						}
						else
							cout << "Name size should be <= " << nameSize - 1;

					}
					

					WriteFile(
						hNamedPipe,
						(char*)&newEmpl,
						sizeof(Employee),
						&dwBytesWritten,
						(LPOVERLAPPED)NULL
					);

					ReleaseMutex(fileMutex);
				}
			}
			else {
				cout << "Not found an employee with id: " << cm.arg << endl;
			}
		}
		else {
			cout << "Unknown command" << endl;
		}
		

		

	}
	CloseHandle(hNamedPipe);
	
	cout << "Server was closed" << endl;
	return 0;
}