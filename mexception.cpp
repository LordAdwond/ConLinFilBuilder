#include "mexception.h"

NonSquareMatrixException::NonSquareMatrixException()
{
	this->description = "Nonsquare matrix";
}

SingularMatrixException::SingularMatrixException()
{
	this->description = "Singular matrix (can't be inverted)";
}

CantBeAddedException::CantBeAddedException()
{
	this->description = "Matrices can't be added";
}

CantBeMultipliedException::CantBeMultipliedException()
{
	this->description = "Matrices can't be multiplied";
}

CantBeInversedException::CantBeInversedException()
{
	this->description = "Matrix can't be inversed";
}

DivisionByZeroException::DivisionByZeroException()
{
	this->description = "Division by zero";
}

CantBeBuiltException::CantBeBuiltException()
{
	this->description = "Linear filter can't be built";
}