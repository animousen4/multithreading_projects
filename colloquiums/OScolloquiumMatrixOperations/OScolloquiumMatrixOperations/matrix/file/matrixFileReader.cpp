#pragma once
#include <fstream>
#include "../matrix.cpp"
class MatrixFileReader {

public:
	Matrix readMatrix(std::istream& stream) {
		int m;
		int n;

		stream >> m >> n;

		Matrix matrix(m, n);

		stream >> matrix;

		return matrix;
	}
};