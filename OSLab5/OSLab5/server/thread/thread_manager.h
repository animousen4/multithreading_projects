#include <Windows.h>

class ThreadManager {
	HANDLE hThread;
	DWORD IDThread;
private:
	void awaitThread() {
		WaitForSingleObject(hThread, INFINITE);
	}

public:
	HANDLE createThread(LPTHREAD_START_ROUTINE function, LPVOID params) {
		hThread = CreateThread(NULL, 0, function, params, 0, &IDThread);
		if (hThread == NULL)
			throw GetLastError();
		return hThread;
	}


	void closeThread() {
		CloseHandle(hThread);
	}

};