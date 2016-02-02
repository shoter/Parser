#pragma once
#include <string>
#include "OperatorType.h"

//https://pl.wikipedia.org/wiki/%C5%81%C4%85czno%C5%9B%C4%87_(matematyka)
enum OperatorAssociation
{
	LEFT =1,
	RIGHT
};

OperatorAssociation getOperatorAssociation(const OperatorType);