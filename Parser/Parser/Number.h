#pragma once
#include "Operation.h"

class Number : public Operation //Operacja zwracania liczby :)
{
public:
	Number(double = 0.0);
	// Inherited via Operation
	virtual double Result() override;
private :
	double number;

};