#pragma once
#include "Operation.h"
#include "Number.h"
class Multiply : public Operation
{
public:
	Multiply(Operation & lhm, Operation & rhm);
	// Inherited via Operation
	virtual double Result() override;
private:
	Number result;
};