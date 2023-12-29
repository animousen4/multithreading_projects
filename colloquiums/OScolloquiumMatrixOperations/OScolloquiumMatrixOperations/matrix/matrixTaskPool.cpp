#pragma once
#include <stack>
#include "matrixTask.cpp"
#include <Windows.h>
class MatrixTaskPool {

	HANDLE taskMutex;

	std::stack<MatrixTask> taskStack;
public:

	MatrixTaskPool(HANDLE taskMutex) {
		this->taskMutex = taskMutex;

	}
	void addTask(MatrixTask task) {
		taskStack.push(task);
	}

	void initTasks(int m, int n) {
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				addTask(MatrixTask{ i, j });
			}
		}
	}

	
	MatrixTask getTaskSync() {
		WaitForSingleObject(taskMutex, INFINITE);
		MatrixTask task;
		if (taskStack.empty())
			task = MatrixTask{ -1, -1 };
		else {
			task = taskStack.top();
			taskStack.pop();
		}
		ReleaseMutex(taskMutex);

		return task;
	}
};