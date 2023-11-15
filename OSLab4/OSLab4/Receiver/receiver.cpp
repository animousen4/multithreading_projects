
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
	leftMessages += file.get();

	bool haveMessages = !file.fail();
	while (!file.fail()) {
		leftMessages += file.get();
	}

	if (haveMessages) {
		leftMessages.erase(leftMessages.end() - 1);
	}

	return leftMessages;
}

void rewriteLeftMessages(fstream& file, wchar_t* fileName, string& messages) {
	file.open(fileName, ios::binary | ios::out | ios::trunc);

	file.write(messages.c_str(), messages.length());
	file.flush();

	file.close();
}

void readFromFile(wchar_t* fileName, HANDLE& fileMutex, HANDLE& messageAmountSemaphore) {
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
int main(char** args, int argCount) {
	wchar_t* fileName = new wchar_t[maxFileNameSize];
	wchar_t* message;

	int messagesAmount;
	int senderAmount;

	wcout << L"Enter file Name: ";
	wcin.getline(fileName, maxFileNameSize);

	wcout << L"Enter messages Amount: ";
	wcin >> messagesAmount;

	wcout << L"Enter process Amount: ";
	wcin >> senderAmount;

	wofstream binFile("file.bin", ios::binary);

	ProcessManager* managers = new ProcessManager[senderAmount];
	HANDLE fileMutex = CreateMutex(NULL, TRUE, fileMutexName);
	HANDLE messageAmountSemaphore = CreateSemaphore(NULL, messagesAmount, messagesAmount, messageAmountSemaphoreName);

	for (int i = 0; i < senderAmount; i++) {
		wcout << managers[i].createApp(L"Sender.exe", fileName) << " ";
	}

	string command;

	while (true) {
		cin >> command;
		if (command == "f")
			break;
		if (command == "r") {
			readFromFile(fileName, fileMutex, messageAmountSemaphore);
		}

	}



	


	getwchar();



}