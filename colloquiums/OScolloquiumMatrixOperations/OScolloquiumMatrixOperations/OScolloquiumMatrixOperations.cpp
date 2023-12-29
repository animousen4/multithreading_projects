#include "OScolloquiumMatrixOperations.h"
#include <Windows.h>
#include <fstream>
#include "matrix/matrix.cpp"
#include "matrix/matrixTaskPool.cpp"
#include "matrix/matrixInputTask.cpp"
#include "matrix/thread/calculateThread.cpp"
#include "matrix/file/matrixFileReader.cpp"
const int THREAD_OPERATION_DELAY = 100;
int main()
{	
	int threadsAmount;
	HANDLE* hThreads;
	DWORD* idThreads;

	HANDLE taskMutex = CreateMutexA(NULL, FALSE, "taskMutex");
	HANDLE resultMutex = CreateMutexA(NULL, FALSE, "resultMutex");
	HANDLE startEvent = CreateEventA(NULL, true, false, "startEvent");

	std::ifstream inputFile("inputFile.txt");

	MatrixFileReader reader;
	Matrix first = reader.readMatrix(inputFile);
	Matrix second = reader.readMatrix(inputFile);
	inputFile.close();


	MatrixInputTask matrixInputTask = MatrixInputTask::createTask(
		&first,
		&second
	);

	std::cout << "Threads amount: ";
	std::cin >> threadsAmount;

	MatrixTaskPool taskPool(taskMutex);
	taskPool.initTasks(matrixInputTask.resultMatrix->m, matrixInputTask.resultMatrix->n);

	hThreads = new HANDLE[threadsAmount];
	idThreads = new DWORD[threadsAmount];

	ThreadArgs* args = new ThreadArgs{
		&matrixInputTask,
		&taskPool,
		resultMutex,
		startEvent,
		THREAD_OPERATION_DELAY
	};

	for (int i = 0; i < threadsAmount; i++) {
		hThreads[i] = CreateThread(NULL, 0, threadFunc, args, 0, &idThreads[i]);
	}
	
	SetEvent(startEvent);

	WaitForMultipleObjects(threadsAmount, hThreads, true, INFINITE);

	std::cout << *matrixInputTask.resultMatrix;
}
