#include "mmatrix.h"
#include "mexception.h"
#include <vector>
#include <cmath>
#include <iostream>

using namespace std;

// constructors and destructors
mmatrix::mmatrix()
{
	matrix = vector<vector<double>>();
	rows = 0; 
	columns = 0;
}

mmatrix::mmatrix(vector<vector<double>> A, unsigned int n, unsigned int m)
{
	matrix = A;
	rows = n;
	columns = m;
}

mmatrix::mmatrix(mmatrix* other)
{
	matrix = other->matrix;
	rows = other->rows;
	columns = other->columns;
}

mmatrix::~mmatrix()
{
	matrix.clear();
	rows = 0;
	columns = 0;
}

// matrix manipulations
mmatrix* mmatrix::transond()
{
	vector<vector<double> > new_matrix;
	int i{};

	new_matrix.resize(this->columns);
	for (i=0; i<new_matrix.size(); ++i)
	{
		new_matrix[i].resize(this->rows);
	}
	
	for (i = 0; i < this->columns; ++i)
	{
		for (int j = 0; j < this->rows; ++j)
		{
			new_matrix[i][j] = this->matrix[j][i];
		}
	}

	return new mmatrix(new_matrix, columns, rows);
}

double mmatrix::norm()
{
	double S = 0;

	for (auto row : matrix)
	{
		for (auto a : row)
		{
			S += pow(a, 2);
		}
	}

	return sqrt(S);
}

bool mmatrix::is_square()
{
	return rows == columns;
}

void mmatrix::operator=(mmatrix* other)
{
	this->matrix.clear();
	this->matrix = other->matrix;
	this->rows = other->rows;
	this->columns = other->columns;
}

mmatrix* mmatrix::operator+(mmatrix* other) throw(CantBeAddedException)
{
	if (this->rows != other->rows || this->columns != other->columns) throw CantBeAddedException();

	vector<vector<double> > new_matrix = this->matrix;
	for (int i = 0; i < this->rows; ++i)
	{
		for (int j = 0; j < this->columns; ++j)
		{
			new_matrix[i][j] += other->matrix[i][j];
		}
	}

	return new mmatrix(new_matrix, this->rows, this->columns);
}

mmatrix* mmatrix::operator*(mmatrix* other) throw(CantBeMultipliedException)
{
	// if (this->columns != other->rows) throw CantBeMultipliedException();

	vector<vector<double> > new_matrix;
	int i{}, j{}, k{};

	new_matrix.resize(this->rows);
	for (i = 0; i<new_matrix.size(); ++i)
	{
		new_matrix[i].resize(other->columns);
	}

	for (i = 0; i < this->rows; ++i)
	{
		for (j = 0; j < other->columns; ++j)
		{
			for (k = 0; k < this->columns; ++k)
			{
				new_matrix[i][j] += this->matrix[i][k] * other->matrix[k][j];
			}
		}
	}

	return new mmatrix(new_matrix, this->columns, other->columns);
}

mmatrix* mmatrix::operator*(double k)
{
	vector<vector<double> > new_matrix = this->matrix;
	int i{}, j{};

	for (i = 0; i < this->rows; ++i)
	{
		for (j = 0; j < this->columns; ++j)
		{
			new_matrix[i][j] *= k;
		}
	}

	return new mmatrix(new_matrix, this->rows, this->columns);
}


mmatrix* mmatrix::inverse()
{
	if (rows != columns) throw CantBeInversedException();

	vector<vector<double> > E_matrix;
	int i{};

	E_matrix.resize(this->rows);
	for (i = 0; i<E_matrix.size(); ++i)
	{
		E_matrix[i].resize(this->columns);
	}
	for (i = 0; i < this->rows; ++i)
	{
		E_matrix[i][i] = 1;
	}
	auto E = new mmatrix(E_matrix, this->rows, this->columns);

	auto B = *(this->transond()) * this;
	double r = B->norm();
	auto C = *B * (1/r);
	auto D = *E + (*C)*(-1);
	auto X = E;
	auto new_X = *((*D) * (X)) + E;
	int iterations = 0, iterations_limit = 5000;

	while ((*X + (*new_X)*(-1))->norm() >= 0.0000001 && iterations<=iterations_limit+1)
	{
		X = new_X;
		new_X = *((*D) * (X)) + E;
		iterations++;
	}

	return *((*new_X) * this->transond()) * (1/r);
}

// getting matrix
vector< vector<double> > mmatrix::getMatrix()
{
	return this->matrix;
}