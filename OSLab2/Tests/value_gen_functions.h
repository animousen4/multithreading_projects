#pragma once

namespace ValueGeneratorFunctions {

	inline void fillValuesAsk(int* n, int size) {
		for (int i = 0; i < size; i++)
			n[i] = i;
	}

	inline void fillValuesSame(int* n, int size, int value) {
		for (int i = 0; i < size; i++)
			n[i] = value;
	}

	inline void fillValuesDesk(int* n, int size) {
		for (int i = 0; i < size; i++)
			n[size - 1 - i] = i;
	}

}