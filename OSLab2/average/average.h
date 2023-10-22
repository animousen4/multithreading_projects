#include <iostream>
#include <Windows.h>
#include "../entities/entities.h"
struct AverageArgs {
	SizedArray* arr;
	double* avg;

	AverageArgs(SizedArray& a) : arr(&a), avg(new double(0)) {
		
	}

	void setAvg(double av) {
		*avg = av;
	}

	void setError() {
		delete avg;
		avg = nullptr;
	}
};
class Average {
public:
	static DWORD WINAPI average(LPVOID sId) {

		AverageArgs* args = static_cast<AverageArgs*>(sId);
		SizedArray c = *(args->arr);
		int sum = 0;
		if (c.n < 1) {
			args->setError();
			std::cout << "No Average\n";
			return 1;
		}

		for (int i = 0; i < c.n; i++) {
			sum += c.arr[i];
			Sleep(12);
		}

		args->setAvg(sum / (double)c.n);

		std::cout << "AVG: " << *args->avg << std::endl;
	}
};