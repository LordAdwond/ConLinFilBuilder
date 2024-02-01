#pragma once
#include <vector>
#include "mexception.h"

using namespace std;

class mmatrix
{
	vector< vector<double> > matrix;
	bool is_square();
public:
	unsigned int rows, columns;

	mmatrix();
	mmatrix( vector<vector<double> >, unsigned int, unsigned int);
	mmatrix(mmatrix*);
	~mmatrix();

	mmatrix* transond();
	double norm();
	mmatrix* inverse() throw(CantBeInversedException);
	vector< vector<double> > getMatrix();

	void operator=(mmatrix*);
	mmatrix* operator+(mmatrix*) throw(CantBeAddedException);
	mmatrix* operator*(mmatrix*) throw(CantBeMultipliedException);
	mmatrix* operator*(double);
	/*
	mmatrix* operator/(mmatrix*) throw(CantBeInversedException, CantBeMultipliedException);
	mmatrix* operator/(double) throw(DivisionByZeroException);
	*/
};

