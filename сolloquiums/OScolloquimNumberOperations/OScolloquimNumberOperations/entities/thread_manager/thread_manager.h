#include <windows.h>

class ThreadManager {
public:
	
	void createThread(LPTHREAD_START_ROUTINE function, LPVOID params) {
		hThread = CreateThread(NULL, 0, function, params, 0, &IDThread);
		if (hThread == NULL)
			throw GetLastError();
	}

	HANDLE getHThread() {
		return hThread;
	}

private:
	HANDLE hThread;
	DWORD IDThread;

	void closeThread() {
		CloseHandle(hThread);
	}

	~ThreadManager() {
		closeThread();
	}

};