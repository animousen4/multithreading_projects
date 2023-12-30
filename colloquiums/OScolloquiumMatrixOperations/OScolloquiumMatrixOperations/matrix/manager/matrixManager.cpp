#pragma once
#include <Windows.h>
#include "../file/matrixFileReader.cpp"
#include "../matrixTaskPool.cpp"
#include "../thread/calculateThread.cpp"
#include "../thread/threadConsts.cpp"
class MatrixManager {
	int threadsAmount;
	HANDLE* hThreads;
	DWORD* idThreads;
	HANDLE taskMutex;
	HANDLE resultMutex;
	HANDLE startEvent;

	MatrixTaskPool* taskPool;
	MatrixInputTask* matrixInputTask;
	

	Matrix firstMatrix;
	Matrix secondMatrix;

	void startProcesses(ThreadArgs* threadArgs) {
		for (int i = 0; i < threadsAmount; i++) {
			hThreads[i] = CreateThread(NULL, 0, threadFunc, threadArgs, 0, &idThreads[i]);
		}
	}
public:
	MatrixManager(Matrix& m1, Matrix& m2, int threadsAmount) {
		firstMatrix = m1;
		secondMatrix = m2;
		this->threadsAmount = threadsAmount;

		hThreads = new HANDLE[threadsAmount];
		idThreads = new DWORD[threadsAmount];

	}
	bool isValid() {
		
	}
	Matrix calculateSync() {
		return calculateSync(THREAD_OPERATION_DELAY);
	}
	Matrix calculateSync(int operationDelay) {
		taskMutex = CreateMutexA(NULL, FALSE, "taskMutex");
		resultMutex = CreateMutexA(NULL, FALSE, "resultMutex");
		startEvent = CreateEventA(NULL, true, false, "startEvent");

		matrixInputTask = MatrixInputTask::createTask(&firstMatrix, &secondMatrix);
		taskPool = new MatrixTaskPool(
			taskMutex,
			matrixInputTask->resultMatrix->m,
			matrixInputTask->resultMatrix->n
		);

		ThreadArgs* threadArgs = new ThreadArgs{
			matrixInputTask,
			taskPool,
			resultMutex,
			startEvent,
			operationDelay
		};

		startProcesses(threadArgs);
		SetEvent(startEvent);

		WaitForMultipleObjects(threadsAmount, hThreads, true, INFINITE);

		return *matrixInputTask->resultMatrix;
	}

};