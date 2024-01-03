#include <gtest/gtest.h>
#include "../average/average.h"
#include "value_gen_functions.h"

namespace AverageTesting {

	AverageArgs createArgs(int* elements, int elementAmount) {

		SizedArray sizedArray{ elements, elementAmount };

		return AverageArgs{sizedArray};
	}

	TEST(AverageTest, CalculateAverageTestCaseAsk) {


		int* arr = new int[5];
		SizedArray sizedArr = SizedArray{ arr, 5 };
		AverageArgs* as = new AverageArgs{ sizedArr };

		ValueGeneratorFunctions::fillValuesAsk(arr, 5);

		Average::average(as);

		EXPECT_EQ(2.0, *as->avg);
	}

	TEST(AverageTest, CalculateAverageTestCaseDesk) {


		int* arr = new int[5];
		SizedArray sizedArr = SizedArray{ arr, 5 };
		AverageArgs* as = new AverageArgs{ sizedArr };

		ValueGeneratorFunctions::fillValuesDesk(arr, 5);

		Average::average(as);

		EXPECT_EQ(2.0, *as->avg);
	}

	TEST(AverageTest, CalculateAverageCaseSame) {


		int* arr = new int[12];
		SizedArray sizedArr = SizedArray{ arr, 12 };
		AverageArgs* as = new AverageArgs{ sizedArr };

		ValueGeneratorFunctions::fillValuesSame(arr, 12, 4);

		Average::average(as);

		EXPECT_EQ(4.0, *as->avg);
	}

	TEST(AverageTest, CalculateAverageNotPossibleCase) {


		int* arr = new int[0];
		SizedArray sizedArr = SizedArray{ arr, 0 };
		AverageArgs* as = new AverageArgs{sizedArr};

		Average::average(as);

		EXPECT_EQ(nullptr, as->avg);

	}

}