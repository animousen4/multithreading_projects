#include <windows.h>
#include <iostream>
#include <string>
#include <fstream>
#include "../entities/Employee.cpp";
#include "../entities/Command.cpp"
#include "../entities/EmployeeResponse.cpp"
using namespace std;

int main()
{	


	char c; 
	HANDLE hNamedPipe;
	char pipeName[] = "\\\\.\\pipe\\demo_pipe";

	if (!WaitNamedPipe(TEXT("\\\\.\\pipe\\demo_pipe"), NMPWAIT_WAIT_FOREVER)) {
		printf("Error waiting for named pipe\n");
		return 1;
	}

	hNamedPipe = CreateFileA(
		pipeName,
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
		cout << "Press any char to finish the client: ";
		cin >> c;
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

			cout << resp.empl << endl;

			if (cm.command[0] == 'm') {
				Employee newEmpl;
				cout << "Enter the changes:" << endl;
				cout << "id\tname\thours" << endl;

				cin >> newEmpl;

				WriteFile(
					hNamedPipe,
					(char*)&newEmpl,
					sizeof(Employee),
					&dwBytesWritten,
					(LPOVERLAPPED)NULL
				);
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