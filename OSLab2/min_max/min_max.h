#include <iostream>
#include <windows.h>
#include "../entities/entities.h"

struct MinMaxArgs {
	SizedArray* c;
	int* maxIndex;
	int* minIndex;

	MinMaxArgs(SizedArray& _c):
		c(&_c),
		maxIndex(new int(0)),
		minIndex(new int(0))
	{
		
	}

	void setMaxIndex(int index) {
		*maxIndex = index;
	}

	void setMinIndex(int index) {
		*minIndex = index;
	}

	void setError() {
		delete maxIndex;
		delete minIndex;

		maxIndex = nullptr;
		minIndex = nullptr;
	}
};

class MinMax {
public:
	static DWORD WINAPI minMax(LPVOID sId) {
		int minIndex;
		int maxIndex;

		MinMaxArgs* args = static_cast<MinMaxArgs*>(sId);

		if (args->c->n < 1) {
			args->setError();
			std::cout << "No max or min\n";
			return 1;
		}

		maxIndex = 0;
		minIndex = 0;

		for (int i = 1; i < args->c->n; i++) {
			if (args->c->arr[i] > args->c->arr[maxIndex])
				maxIndex = i;
			else
				if (args->c->arr[i] < args->c->arr[minIndex])
					minIndex = i;
			Sleep(7);
		}

		args->setMaxIndex(maxIndex);
		args->setMinIndex(minIndex);

		std::cout << "MAX: " << args->c->arr[maxIndex] << "\nMIN: " << args->c->arr[minIndex] << std::endl;
	};
};