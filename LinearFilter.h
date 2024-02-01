#pragma once
#include "mexception.h"
#include "mmatrix.h"
#include <vector>

struct FilterData;

class LinearFilter
{
	unsigned int DataLen;
	unsigned int k;
	double* data;
	double* coefs;

	void solve() throw(CantBeBuiltException);
public:
	LinearFilter();
	LinearFilter(unsigned int, double*);
	LinearFilter(unsigned int, unsigned int, double*);

	void resetData(unsigned int, double*);
	void resetData(unsigned int, unsigned int, double*);

	FilterData getFilterData();
};

struct FilterData
{
	unsigned int ElementsNumber;
	double* elements;
};