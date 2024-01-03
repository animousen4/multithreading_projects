#include <gtest/gtest.h>
#include "../min_max/min_max.h"
#include "value_gen_functions.h"

namespace MaxMinTesting {

	MinMaxArgs createArgs(int* elements, int elementAmount) {

		SizedArray sizedArray{ elements, elementAmount };

		return MinMaxArgs{ sizedArray };
	}

	TEST(MaxTest, CalculateMaxIndexTest) {
		
		MinMaxArgs args = createArgs(new int[5], 5);
		ValueGeneratorFunctions::fillValuesAsk(args.c->arr, args.c->n);

		MinMax::minMax(&args);

		EXPECT_EQ(4, *args.maxIndex);
	}

	TEST(MaxTest, CalculateMaxDescIndexTest) {

		MinMaxArgs args = createArgs(new int[5], 5);
		ValueGeneratorFunctions::fillValuesDesk(args.c->arr, args.c->n);

		MinMax::minMax(&args);

		EXPECT_EQ(0, *args.maxIndex);
	}

	TEST(MaxTest, CalculateSameMaxIndexTest) {

		MinMaxArgs args = createArgs(new int[5], 5);
		ValueGeneratorFunctions::fillValuesSame(args.c->arr, args.c->n, 3);

		MinMax::minMax(&args);

		EXPECT_EQ(0, *args.maxIndex);
	}

	TEST(MinTest, CalculateMinIndexTest) {

		MinMaxArgs args = createArgs(new int[5], 5);
		ValueGeneratorFunctions::fillValuesAsk(args.c->arr, args.c->n);

		MinMax::minMax(&args);

		EXPECT_EQ(0, *args.minIndex);
	}

	TEST(MinTest, CalculateMinIndexDeskTest) {

		MinMaxArgs args = createArgs(new int[5], 5);
		ValueGeneratorFunctions::fillValuesDesk(args.c->arr, args.c->n);

		MinMax::minMax(&args);

		EXPECT_EQ(4, *args.minIndex);
	}

	TEST(MinTest, CalculateSameMinIndexTest) {

		MinMaxArgs args = createArgs(new int[5], 5);
		ValueGeneratorFunctions::fillValuesSame(args.c->arr, args.c->n, 777);

		MinMax::minMax(&args);

		EXPECT_EQ(0, *args.minIndex);
	}
}