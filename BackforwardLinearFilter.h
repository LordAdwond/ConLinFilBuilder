#pragma once
#include "mexception.h"
#include "mmatrix.h"
#include <vector>

struct BackforwardFilterData;

class BackforwardLinearFilter
{
	unsigned int DataLen;
	unsigned int k;
	double* data;
	double* coefs;

	void solve() throw(CantBeBuiltException);
public:
	BackforwardLinearFilter();
	BackforwardLinearFilter(unsigned int, double*);
	BackforwardLinearFilter(unsigned int, unsigned int, double*);

	void resetData(unsigned int, double*);
	void resetData(unsigned int, unsigned int, double*);

	BackforwardFilterData getFilterData();
};

struct BackforwardFilterData
{
	unsigned int ElementsNumber;
	double* elements;
};