#pragma once
#include <iostream>

class Matrix {

public:
	int m;
	int n;

	int** matrix;
	Matrix() {
	
	}
	Matrix(int m, int n) {
		this->m = m;
		this->n = n;

		matrix = new int* [m];
		for (int i = 0; i < m; i++)
			matrix[i] = new int[n];
	}
	
	void setElement(int m, int n, int element) {
		matrix[m][n] = element;
	}

	

	friend std::istream& operator >>(std::istream& stream, Matrix& matrix) {
		for (int i = 0; i < matrix.m; i++)
			for (int j = 0; j < matrix.n; j++)
				stream >> matrix.matrix[i][j];

		return stream;
	}

	friend std::ostream& operator <<(std::ostream& stream, const Matrix& matrix) {
		for (int i = 0; i < matrix.m; i++) {
			for (int j = 0; j < matrix.n; j++)
				stream << matrix.matrix[i][j] << "\t";
			stream << std::endl;
		}

		return stream;
	}

	static Matrix* zeroMatrix(int m, int n) {
		Matrix* matrix = new Matrix(m, n);

		for (int i = 0; i < m; i++)
			for (int j = 0; j < n; j++)
				matrix->matrix[i][j] = 0;

		return matrix;
	}
};