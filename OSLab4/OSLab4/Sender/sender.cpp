

#include <iostream>
#include <windows.h>
#include "../consts.cpp"
using namespace std;


int main(int argCount, char** args) {
	HANDLE hStartEvent = OpenEvent(SYNCHRONIZE, FALSE, startSenderName);

	cout << hStartEvent << "\n";

	WaitForSingleObject(hStartEvent, INFINITE);

	for (int i = 0; i < argCount; i++)
		cout << args[i] << " ";

	cout << argCount;


	system("pause");

}