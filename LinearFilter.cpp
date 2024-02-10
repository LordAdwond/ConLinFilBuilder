#include "LinearFilter.h"
#include "mexception.h"
#include "mmatrix.h"
#include <vector>
#include <cmath>
#include <iostream>

using namespace std;

LinearFilter::LinearFilter() : DataLen(0), k(0), data(nullptr), coefs(nullptr) {};
LinearFilter::LinearFilter(unsigned int elem_num, double* data_array) : DataLen(elem_num), k(0), data(data_array), coefs(nullptr) 
{
	this->k = floor(sqrt(this->DataLen));
	this->coefs = new double[this->k];
	this->solve();
};
LinearFilter::LinearFilter(unsigned int elem_num, unsigned int K, double* data_array) : DataLen(elem_num), k(K), data(data_array), coefs(nullptr) 
{
	this->coefs = new double[this->k];
	this->solve();
};


void LinearFilter::resetData(unsigned int new_elem_num, double* new_data_array)
{
	this->DataLen = new_elem_num;
	this->data = new_data_array;

	this->solve();
}
void LinearFilter::resetData(unsigned int new_elem_num, unsigned int new_k, double* new_data_array)
{
	this->DataLen = new_elem_num;
	this->k = new_k;
	this->data = new_data_array;
}

FilterData LinearFilter::getFilterData()
{
	FilterData package;
	package.ElementsNumber = this->k;
	package.elements = this->coefs;

	return package;
}

void LinearFilter::solve() throw(CantBeBuiltException)
{
	// primary data
	vector< vector<double> > matrix;
	vector< vector<double> > v;
	int i{}, j{};

	matrix.resize(this->DataLen - this->k);
	for (i = 0; i < this->DataLen - this->k; ++i)
	{
		matrix[i].resize(this->k);
	}
	for (i = 0; i < this->DataLen - this->k; ++i)
	{
		for (j = 0; j < this->k; ++j)
		{
			matrix[i][j] = *(this->data + i + j);
		}
	}

	v.resize(this->DataLen - this->k);
	for (i = 0; i < this->DataLen - this->k; ++i)
	{
		v[i].resize(1);
	}
	for (i = 0; i < this->DataLen - this->k; ++i)
	{
		v[i][0] = *(this->data + i + this->k);
	}

	// calculation of linear filter
	mmatrix* A = new mmatrix(matrix, this->DataLen - this->k, this->k);
	mmatrix* b = new mmatrix(v, DataLen - this->k, 1);
	mmatrix* a = new mmatrix();

	auto new_A = *(A->transond()) * A;
	new_A->columns = new_A->getMatrix()[0].size();
	new_A->rows = new_A->getMatrix().size();

	auto new_b = *(A->transond()) * b;
	a = *(new_A->inverse()) * new_b;
	auto coeficients = a->getMatrix();
	for (i = 0; i < this->k; ++i)
	{
		*(this->coefs + i) = coeficients[i][0];
	}
}
