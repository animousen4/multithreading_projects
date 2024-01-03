// OSLab2.cpp : Defines the entry point for the application.
//

#include "main.h"
#include "../min_max/min_max.h"
#include "../average/average.h"
#include "../thread_manager/thread_manager.h"
#include "../entities/entities.h"

int main()
{	
	SizedArray array;
	std::cout << "Array size: ";
	std::cin >> array.n;

	array.initArray();
	array.userInputArray();

	std::cout << std::endl;

	ThreadManager minMaxManager;
	ThreadManager avgManager;

	MinMaxArgs mmArgs = MinMaxArgs{array};
	AverageArgs avgArgs = AverageArgs{array};
	minMaxManager.createThread(MinMax::minMax, &mmArgs);
	avgManager.createThread(Average::average, &avgArgs);
	
	minMaxManager.processThread();
	avgManager.processThread();

	if (mmArgs.maxIndex != nullptr && avgArgs.avg != nullptr) {
		array.arr[*mmArgs.maxIndex] = *avgArgs.avg;
		array.arr[*mmArgs.minIndex] = *avgArgs.avg;

		std::cout << "Res array:" << std::endl;
		array.printArray();
	}
	else {
		std::cout << "Can't change min, max to avg";
	}
	std::cout << std::endl;

	system("pause");
	return 0;
}
