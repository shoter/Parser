#pragma once
#include "Operation.h"
#include "Number.h"
class Power : public Operation
{
public:
	Power(Operation & lhm, Operation & rhm);
	// Inherited via Operation
	virtual double Result() override;
private:
	Number result;
};