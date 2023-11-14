

#include <iostream>

using namespace std;


int main(int argCount, char** args) {
	for (int i = 0; i < argCount; i++)
		cout << args[i] << " ";

	cout << argCount;
	system("pause");

}