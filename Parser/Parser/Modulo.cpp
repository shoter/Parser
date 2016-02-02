#include "Modulo.h"
#include <math.h>
#include "Utils.h"
#include "DivideByZeroException.h"

Modulo::Modulo(Operation & lhm, Operation & rhm)
{
	if (Compare(rhm, 0.0))
		throw new DivideByZeroException();
	result = fmod(lhm, rhm);
}

double Modulo::Result()
{
	return result;
}
