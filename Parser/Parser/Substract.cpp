#include "Substract.h"

Substract::Substract(Operation & lhm, Operation & rhm)
	:Add(lhm, Number(-rhm)) //sprytnie wykorzystamy dodawanie :). Bo jak wiemy odejmowanie to dodawanie ujemnej liczby!
{
}

double Substract::Result()
{
	return Add::Result();
}
