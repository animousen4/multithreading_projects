
#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include "process/process_manager.h"
#include "../consts.cpp"
using namespace std;

const int maxFileNameSize = 30;

// MUTEX:
// SIGNAL - NO ONE THREAD ATTACHED;
// NON-SIGNAL - ATTACHED AT LEAST TO ONE;

// SEMAPHORE:
// SIGNAL - VALUE>0
// NON-SIGNAL - VALUE=0
// -1 IN WAITFOR...
// +N in ReleaseSemaphore(HANDLE, LONG, LPLONG)

string getLeftMessages(fstream& file) {
	string leftMessages;
	char c;
	bool ok = true;
	while (ok) {
		c = file.get();
		if (!file.fail())
			leftMessages += c;
		else
			ok = false;
	}

	return leftMessages;
}

void rewriteLeftMessages(fstream& file, string fileName, string& messages) {
	file.open(fileName, ios::binary | ios::out | ios::trunc);

	file.write(messages.c_str(), messages.length());
	file.flush();

	file.close();
}

void readFromFile(string fileName, HANDLE& fileMutex, HANDLE& messageAmountSemaphore) {
	bool fileSuccess = false;
	char message[messageSize];
	fstream file;
	while (!fileSuccess) {
		// Wait other to be finished
		WaitForSingleObject(fileMutex, INFINITE);

		file.open(fileName, ios::binary | ios::in);
		file.read(message, messageSize);
		
		fileSuccess = !file.fail();
		
		string leftMessages = getLeftMessages(file);

		file.close();

		rewriteLeftMessages(file, fileName, leftMessages);

		// releasing file
		ReleaseMutex(fileMutex);
	}

	// +1 SLOT TO MESSAGES
	ReleaseSemaphore(messageAmountSemaphore, 1, NULL);

	// out read message;
	cout << message;
}

string programName = "[RECEIV]";
int main(char** args, int argCount) {
	string fileName;
	char* message;

	int messagesAmount;
	int senderAmount;

	cout << "Enter file Name: ";
	cin >> fileName;

	cout << "Enter messages Amount: ";
	cin >> messagesAmount;

	cout << "Enter process Amount: ";
	cin >> senderAmount;

	ProcessManager* managers = new ProcessManager[senderAmount];

	// To wait for everyone is ready
	HANDLE* startHandlersSemaphores = new HANDLE[senderAmount];
	HANDLE fileMutex = CreateMutex(NULL, FALSE, fileMutexName);
	HANDLE messageAmountSemaphore = CreateSemaphore(NULL, messagesAmount, messagesAmount, messageAmountSemaphoreName);
	for (int i = 0; i < senderAmount; i++) {
		string semName = string(startSemaphoreName) + "_" + to_string(i);
		startHandlersSemaphores[i] = CreateSemaphore(NULL, 0, 1, semName.c_str());
		managers[i].createApp("Sender.exe", fileName);
	}

	cout << "Waiting for all programms to be opened\n";
	//WaitForSingleObject()
	cout << "All programms has been opened.\nStarted\n\n";

	cout << "Commands:\nf - finish\nr - read\n\n";
	string input;

	while (true) {
		cout << programName + "$ ";
		cin >> input;
		if (input == "f")
			break;
		else
			if (input == "r") {
				readFromFile(fileName, fileMutex, messageAmountSemaphore);
				cout << endl;
			}
				else
					cout << "Not supported command. Try again\n";

	}

	CloseHandle(fileMutex);
	CloseHandle(messageAmountSemaphore);

	cout << endl;
	system("pause");

	return 0;

}