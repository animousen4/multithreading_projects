#include "OScolloquiumMatrixOperations.h"
#include <Windows.h>
#include "matrix/matrix.cpp"
#include "matrix/matrixTaskPool.cpp"
#include "matrix/matrixInputTask.cpp"
using namespace std;

int main()
{	
	HANDLE taskMutex = CreateMutexA(NULL, FALSE, "taskMutex");
	MatrixTaskPool taskPool(taskMutex);

	MatrixInputTask matrixInputTask = matrixInputTask.createTask(
		new Matrix(2, 2),
		new Matrix(2, 2)
	);
	
}
