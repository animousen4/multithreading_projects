

#include <iostream>
#include <fstream>
#include <windows.h>
#include "../consts.cpp"
using namespace std;
string programName = "[SENDER]";
bool sendMessage(char* fileName, string message, HANDLE& fileMutex, HANDLE& messageAmountSemaphore) {
	if (message.length() > 20)
		return false;

	// -1 message or Wait

	WaitForSingleObject(messageAmountSemaphore, INFINITE);
	// wait for not busy file
	WaitForSingleObject(fileMutex, INFINITE);

	

	fstream file(fileName, ios::binary | ios::app | ios::out);
	file.write(message.c_str(), messageSize);
	file.flush();
	file.close();

	// make file not busy
	ReleaseMutex(fileMutex);

	return true;
}
int main(int argCount, char** args) {

	HANDLE fileMutex = OpenMutexA(MUTEX_ALL_ACCESS, TRUE, fileMutexName);
	HANDLE messageAmountSemaphore = OpenSemaphoreA(SEMAPHORE_ALL_ACCESS, TRUE, messageAmountSemaphoreName);
	cout << "File: " << args[1] << endl;
	cout << "Commands:\nf - finish\ns - send MESSAGE20\n\n";

	string input;
	while (true) {
		cout << programName + "$ ";
		cin >> input;

		if (input == "f")
			break;
		if (input == "s") {
			string message;
			cin >> message;
			sendMessage(args[1], message, fileMutex, messageAmountSemaphore);
		}
		else
			cout << "Not supported command. Try again\n";
		
	}

	cout << "Program has finished work\n";

	cout << endl;
	system("pause");

	return 0;

}