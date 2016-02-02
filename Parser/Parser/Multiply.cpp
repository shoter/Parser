#include "Multiply.h"

Multiply::Multiply(Operation & lhm, Operation & rhm)
	:result(lhm * rhm)
{
}

double Multiply::Result()
{
	return result;
}
