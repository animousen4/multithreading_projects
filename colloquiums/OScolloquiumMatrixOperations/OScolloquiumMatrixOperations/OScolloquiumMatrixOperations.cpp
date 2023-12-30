#include "OScolloquiumMatrixOperations.h"
#include <Windows.h>
#include <fstream>
#include "matrix/matrix.cpp"
#include "matrix/manager/matrixManager.cpp"

int main()
{	
	Matrix m1;
	Matrix m2;
	int threadsAmount;

	std::cout << "Threads amount: ";
	std::cin >> threadsAmount;

	std::ifstream inputFile("inputFile.txt");
	if (!inputFile.is_open()) {
		std::cout << "Failed opening file inputFile.txt";
		return 1;
	}
	inputFile >> m1 >> m2;
	inputFile.close();

	MatrixManager matrixManager(m1, m2, threadsAmount);
	Matrix resultMatrix = matrixManager.calculateSync();

	std::cout << resultMatrix;
}
