

#include <iostream>
#include <windows.h>
#include "../consts.cpp"
using namespace std;


int main(int argCount, char** args) {

	HANDLE hStartEvent = OpenEventW(EVENT_ALL_ACCESS, TRUE, TEXT(L"hStartEvent"));

	cout << hStartEvent << "\n";

	WaitForSingleObject(hStartEvent, INFINITE);

	for (int i = 0; i < argCount; i++)
		cout << args[i] << " ";

	cout << argCount;


	system("pause");

	return 0;

}