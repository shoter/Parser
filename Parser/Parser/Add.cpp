#include "Add.h"

Add::Add(Operation & lhm, Operation & rhm)
	:result(lhm + rhm)
{
}

double Add::Result()
{
	return result;
}
