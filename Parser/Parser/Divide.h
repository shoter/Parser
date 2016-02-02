#pragma once
#include "Operation.h"
#include "Number.h"
class Divide : public Operation
{
public:
	Divide(Operation &lhm, Operation &rhm);
	// Inherited via Operation
	virtual double Result() override;
private:
	Number result;
};