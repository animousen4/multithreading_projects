#pragma once

#include <Windows.h>
#include <iostream>

struct SizedArray {
	int* arr;
	int n;

	void initArray() {
		arr = new int[n];
	}

	void userInputArray() {
		for (int i = 0; i < n; i++)
			std::cin >> arr[i];
	}

	void printArray() {
		for (int i = 0; i < n; i++)
			std::cout << arr[i] << " ";
	}
};