#pragma once
#include "Operation.h"
#include "Number.h"
class Add : public Operation
{
public:
	Add(Operation & lhm, Operation & rhm);
	// Inherited via Operation
	virtual double Result() override;
private :
	Number result;
};