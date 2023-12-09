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
	hNamedPipe = CreateFile(
		pipeName,
		GENERIC_ALL, // write and read
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
			return;
	}
	CloseHandle(hNamedPipe);

	cout << "The data are written by the client." << endl
		<< "Press any char to finish the client: ";
	cin >> c;
	return 0;
}