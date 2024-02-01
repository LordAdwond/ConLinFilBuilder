#pragma once
#include <string>

class basic_mexception
{
public:
	std::string description;
};

class NonSquareMatrixException : public basic_mexception
{
public:
	NonSquareMatrixException();
};

class SingularMatrixException : public basic_mexception
{
public:
	SingularMatrixException();
};

class CantBeAddedException : public basic_mexception
{
public:
	CantBeAddedException();
};

class CantBeMultipliedException : public basic_mexception
{
public:
	CantBeMultipliedException();
};

class CantBeInversedException : public basic_mexception
{
public:
	CantBeInversedException();
};

class DivisionByZeroException : public basic_mexception
{
public:
	DivisionByZeroException();
};

class CantBeBuiltException : public basic_mexception
{
public:
	CantBeBuiltException();
};