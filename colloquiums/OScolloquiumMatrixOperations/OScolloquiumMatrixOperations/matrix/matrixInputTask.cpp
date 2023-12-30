#pragma once

#include "matrix.cpp"
struct MatrixInputTask {
	Matrix* firstMatrix;
	Matrix* secondMatrix;

	Matrix* resultMatrix;

	static MatrixInputTask* createTask(Matrix* first, Matrix* second) {
		return new MatrixInputTask{ first, second, new Matrix(first->m, second->n) };
	}
};