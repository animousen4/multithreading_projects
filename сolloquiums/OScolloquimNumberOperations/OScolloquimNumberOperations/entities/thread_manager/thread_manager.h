#include <windows.h>
#include "../action_processor/action_processor.h"

class ThreadManager {
	
private:
	HANDLE* hThread;
	int amount;
	HANDLE createThread(LPTHREAD_START_ROUTINE function, LPVOID params) {
		DWORD iT;
		return CreateThread(NULL, 0, function, params, 0, &iT);
	}

public:
	ThreadManager(int amount) {
		this->amount = amount;

		hThread = new HANDLE[amount];
	}

	void createAllThreads(std::vector<ActionProcessorArgs>& args) {
		for (int i = 0; i < amount; i++) {
			hThread[i] = createThread(ActionProcessor::process, &args[i]);
		}
	}

	void awaitAll() {
		WaitForMultipleObjects(amount, hThread, TRUE, INFINITE);
	}
};