#pragma once 
#include <Windows.h>
#include <iostream>
#include "../matrix.cpp"
#include "../matrixTaskPool.cpp"
#include "../matrixInputTask.cpp"

struct ThreadArgs {
	
	MatrixInputTask* inputTask;
	MatrixTaskPool* matrixTaskPool;

	HANDLE writeResultMatrixMutex;
	HANDLE waitEvent;


};
static void writeResultSync(ThreadArgs args, MatrixTask task, int res) {
	WaitForSingleObject(args.writeResultMatrixMutex, INFINITE);

	args.inputTask->resultMatrix->matrix[task.m][task.n] = res;

	ReleaseMutex(args.writeResultMatrixMutex);
}

static DWORD WINAPI threadFunc(LPVOID sId) {
	ThreadArgs args = *static_cast<ThreadArgs*>(sId);

	WaitForSingleObject(args.waitEvent, INFINITE);

	while (true) {
		MatrixTask task = args.matrixTaskPool->getTaskSync();

		std::cout << "Calculating: " << task.m << " " << task.n << std::endl;
		if (task.hasTask()) {
			int res = 0;

			for (int i = 0; i < args.inputTask->firstMatrix->n; i++) {
				res += args.inputTask->firstMatrix->matrix[task.m][i] * args.inputTask->secondMatrix->matrix[i][task.n];
			}

			std::cout << "Res of calculating: " << task.m << "x" << task.n << " - " << res << std::endl;
			writeResultSync(args, task, res);
		}
		else {
			return 0;
		}

	}

	return 0;

}