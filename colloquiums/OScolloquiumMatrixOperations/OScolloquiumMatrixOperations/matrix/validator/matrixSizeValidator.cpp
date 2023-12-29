#pragma once
#include "matrixValidator.cpp";
#include "../matrix.cpp"

class MatrixSizeValidator : MatrixValidator {


	Matrix first;
	Matrix second;

public:

	MatrixSizeValidator(Matrix& first, Matrix& second) {
		this->first = first;
		this->second = second;
	}

	bool validate() override {
		return first.n == second.m;
	}
};