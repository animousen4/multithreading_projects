

#include <iostream>
#include <fstream>
#include <windows.h>
#include "../consts.cpp"
using namespace std;

bool sendMessage(char* fileName, string message, HANDLE& fileMutex, HANDLE& messageAmountSemaphore) {
	if (message.length() > 20)
		return false;

	// wait for not busy file
	WaitForSingleObject(fileMutex, INFINITE);

	// -1 message or Wait
	WaitForSingleObject(messageAmountSemaphore, INFINITE);

	fstream file(fileName, ios::binary | ios::app | ios::out);
	file.write(message.c_str(), messageSize);
	file.flush();
	file.close();

	// make file not busy
	ReleaseMutex(fileMutex);

	return true;
}
int main(int argCount, char** args) {

	HANDLE mutex = OpenMutexA(MUTEX_ALL_ACCESS, TRUE, fileMutexName);
	//HANDLE semaphore = 
	cout << hStartEvent << "\n";

	WaitForSingleObject(hStartEvent, INFINITE);

	for (int i = 0; i < argCount; i++)
		cout << args[i] << " ";

	cout << argCount;


	system("pause");

	return 0;

}