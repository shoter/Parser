#pragma once
#include "Operation.h"
#include "Number.h"

class Modulo : public Operation // Dzieleni z reszta 5.1 % 2.5 = 0.1
{
public:
	Modulo(Operation & lhm, Operation & rhm);
	// Inherited via Operation
	virtual double Result() override;
private:
	Number result;
};