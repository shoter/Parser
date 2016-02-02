#include "Power.h"
#include <math.h>
Power::Power(Operation & lhm, Operation & rhm)
	:result(pow(lhm, rhm))
{
}

double Power::Result()
{
	return result;
}
