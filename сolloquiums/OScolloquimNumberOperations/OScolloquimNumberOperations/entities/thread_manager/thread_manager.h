#include <windows.h>

class ThreadManager {
public:
	
	void createThread(LPTHREAD_START_ROUTINE function, LPVOID params) {
		hThread = CreateThread(NULL, 0, function, params, 0, &IDThread);
		if (hThread == NULL)
			throw GetLastError();
	}

	void processThread() {
		awaitThread();
		closeThread();
	}

	void doLifeCycle(LPTHREAD_START_ROUTINE function, LPVOID params) {
		createThread(function, params);
		awaitThread();
		closeThread();
	}

	HANDLE getHThread() {
		return hThread;
	}

private:
	HANDLE hThread;
	DWORD IDThread;

	void awaitThread() {
		WaitForSingleObject(hThread, INFINITE);
	}

	void closeThread() {
		CloseHandle(hThread);
	}


};