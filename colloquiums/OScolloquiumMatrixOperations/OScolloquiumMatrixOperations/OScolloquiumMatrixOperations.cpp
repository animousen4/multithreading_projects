#include "OScolloquiumMatrixOperations.h"
#include <Windows.h>
#include "matrix/matrix.cpp"
#include "matrix/matrixTaskPool.cpp"
#include "matrix/matrixInputTask.cpp"
#include "matrix/thread/calculateThread.cpp"
using namespace std;

int main()
{	
	int threadsAmount;
	HANDLE* hThreads;
	DWORD* idThreads;

	HANDLE taskMutex = CreateMutexA(NULL, FALSE, "taskMutex");
	HANDLE resultMutex = CreateMutexA(NULL, FALSE, "resultMutex");
	HANDLE startEvent = CreateEventA(NULL, true, false, "startEvent");
	MatrixTaskPool taskPool(taskMutex);

	MatrixInputTask matrixInputTask = matrixInputTask.createTask(
		Matrix::zeroMatrix(2, 2),
		Matrix::zeroMatrix(2, 2)
	);

	threadsAmount = 2;

	hThreads = new HANDLE[threadsAmount];
	idThreads = new DWORD[threadsAmount];

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			taskPool.addTask(MatrixTask{ i, j });
		}
	}

	ThreadArgs* args = new ThreadArgs{&matrixInputTask, &taskPool, resultMutex, startEvent};
	for (int i = 0; i < threadsAmount; i++) {
		hThreads[i] = CreateThread(NULL, 0, threadFunc, args, 0, &idThreads[i]);
	}
	
	SetEvent(startEvent);

	WaitForMultipleObjects(threadsAmount, hThreads, true, INFINITE);

	for (int i = 0; i < matrixInputTask.resultMatrix->m; i++) {
		for (int j = 0; j < matrixInputTask.resultMatrix->n; j++) {
			cout << matrixInputTask.resultMatrix->matrix[i][j] << "\t";
		}
		cout << std::endl;
	}
}
