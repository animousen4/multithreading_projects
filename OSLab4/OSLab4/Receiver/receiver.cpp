
#include <iostream>
#include <fstream>
#include "process/process_manager.h"
using namespace std;

const int maxFileNameSize = 30;
const int messageSize = 20;
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
	for (int i = 0; i < senderAmount; i++) {
		wcout << managers[i].createApp(L"Sender.exe", fileName) << " ";
	}


}