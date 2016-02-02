#include "Divide.h"
#include "Utils.h"
#include "DivideByZeroException.h"

Divide::Divide(Operation & lhm, Operation & rhm)
{
	if (Compare(rhm, 0.0)) //jesli rowne zero
		throw DivideByZeroException(); //to wywal wyjatek
	result = lhm / rhm;
}

double Divide::Result()
{
	return result;
}
