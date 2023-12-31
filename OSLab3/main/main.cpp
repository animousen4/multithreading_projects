#include "../marker/marker.cpp";
#include "../thread_manager/thread_manager.h"
//#include <windows.h>
#include <iostream>
#include <vector>
using namespace std;

int n;
int* arr;
HANDLE hStartEvent;
HANDLE* hMarkers;
HANDLE* hMarkersNotPossibleEvent;
HANDLE* hMarkersContinueWork;
bool* markersContinueWork;
CRITICAL_SECTION cs;
CRITICAL_SECTION printCS;
CRITICAL_SECTION internPrintCS;



static void printArr() {
	cout << endl;
	cout << "[ARR]: " << endl;
	for (int i = 0; i < n; i++)
		cout << arr[i] << " ";
	cout << endl << "[END OF ARR]" << endl << endl;
}

static void printVec(vector<int>& vec) {
	cout << endl;
	for (auto el : vec)
		cout << el << " ";
	cout << endl;
}
static DWORD WINAPI marker(LPVOID sId) {
	vector<int> markedIndexes;
	MarkerArgs* args = static_cast<MarkerArgs*>(sId);


	// Waiting start of main
	WaitForSingleObject(hStartEvent, INFINITE);

	// start;z`

	srand(args->number);
	int genNum;
	bool isWorking = true;
	while (isWorking) {

		genNum = rand();
		genNum = genNum % n;

		EnterCriticalSection(&cs);

		if (arr[genNum] == 0) {

			Sleep(5);
			arr[genNum] = args->number;
			Sleep(5);

			markedIndexes.push_back(genNum);

			LeaveCriticalSection(&cs);
			
		}
		else {

			LeaveCriticalSection(&cs);

			EnterCriticalSection(&internPrintCS);
				cout << args->number << "\t" << markedIndexes.size() << "\t" << genNum << endl;
			LeaveCriticalSection(&internPrintCS);

			SetEvent(hMarkersNotPossibleEvent[args->number - 1]);
			
			// Waiting for answer from main
			WaitForSingleObject(hMarkersContinueWork[args->number-1], INFINITE);

			EnterCriticalSection(&cs);

			if (!markersContinueWork[args->number-1])
			{	
					isWorking = false;
					for (int i = 0; i < markedIndexes.size(); i++)
						arr[markedIndexes[i]] = 0;
				
			}

			LeaveCriticalSection(&cs);
			
		}

		

		
	}

	return 0;	
}
int getToFinishThread(vector<int>& workingThreads) {
	bool isOkFinish = false;
	int toFinishNumber;
	while (!isOkFinish) {

		cout << endl;
		cout << "Working threads:";
		printVec(workingThreads);
		cout << "To finish thread#: ";
		cin >> toFinishNumber;

		auto it = find(workingThreads.begin(), workingThreads.end(), toFinishNumber);
		if (it != workingThreads.end()) {
			workingThreads.erase(it);
			isOkFinish = true;
		}
		else {
			cout << "\nThread " << toFinishNumber << " not exists, or not working\n";
		}

	}

	return toFinishNumber;
}
int main() {
	int markerThreadAmount;
	ThreadManager* managers;
	vector<int> workingThreads;

	cout << "Arr size: ";
	cin >> n;

	if (n <= 0) {
		cout << "N>0 should be at least" << endl;
		system("pause");
		return 0;
	}

	arr = new int[n];
	for (int i = 0; i < n; i++)
		arr[i] = 0;
	cout << "Marker thread amount: ";
	cin >> markerThreadAmount;

	if (markerThreadAmount < 0) {
		cout << "marker thread amount>0 should be at least" << endl;
		system("pause");
		return 0;
	}


	hStartEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	managers = new ThreadManager[markerThreadAmount];
	hMarkers = new HANDLE[markerThreadAmount];
	hMarkersNotPossibleEvent = new HANDLE[markerThreadAmount];
	hMarkersContinueWork = new HANDLE[markerThreadAmount];
	markersContinueWork = new bool[markerThreadAmount];


	for (int i = 0; i < markerThreadAmount; i++) {
		hMarkers[i] = managers[i].createThread(marker, new MarkerArgs{ i + 1 });
		workingThreads.push_back(i + 1);
		hMarkersNotPossibleEvent[i] = CreateEvent(NULL, TRUE, FALSE, NULL);
		hMarkersContinueWork[i] = CreateEvent(NULL, FALSE, FALSE, NULL);
		markersContinueWork[i] = true;
	}

	int toFinishNumber;
	bool isOkFinish = false;

	// Start markers
	InitializeCriticalSection(&cs);
	InitializeCriticalSection(&printCS);
	InitializeCriticalSection(&internPrintCS);

	SetEvent(hStartEvent);

	while (workingThreads.size() != 0) {

		//WaitForMultipleObjects(markerThreadAmount, hMarkersNotPossibleEvent, TRUE, INFINITE);
		// up to 64

		for (int mW = 0; mW < markerThreadAmount; mW++)
			WaitForSingleObject(hMarkersNotPossibleEvent[mW], INFINITE);

		printArr();
			
		toFinishNumber = getToFinishThread(workingThreads);

		// mark thread as toFinish work
		markersContinueWork[toFinishNumber - 1] = false;
		SetEvent(hMarkersContinueWork[toFinishNumber - 1]);

		// finishing and waiting
		WaitForSingleObject(hMarkers[toFinishNumber - 1], INFINITE);
		managers[toFinishNumber - 1].closeThread();

		cout << "AFTER FINISH:";
		printArr();

		// !!! One killed !!! Resetting as "NOT OK" only for left elements
		// neccessary for main!!!
		for (auto el : workingThreads) {
			ResetEvent(hMarkersNotPossibleEvent[el - 1]);
		}

		for (int i = 0; i < markerThreadAmount; i++)
			if (markersContinueWork[i])
				SetEvent(hMarkersContinueWork[i]);
	}

	DeleteCriticalSection(&cs);
	DeleteCriticalSection(&printCS);
	DeleteCriticalSection(&internPrintCS);

	cout << "The program has finished work\n";

	system("pause");

	return 0;

}