#include "OperatorAssociation.h"
//https://pl.wikipedia.org/wiki/%C5%81%C4%85czno%C5%9B%C4%87_(matematyka)
OperatorAssociation getOperatorAssociation(const OperatorType type)
{
	switch (type)
	{
	case OperatorType::ADD : case OperatorType::SUBSTRACT : case OperatorType::DIVIDE : 
	case OperatorType::MULTIPLY : case OperatorType::MODULO :
		return OperatorAssociation::LEFT;
	case OperatorType::POWER:
		return OperatorAssociation::RIGHT;
	default:
		throw std::exception("getOperatorAssociation wrong value");
	}
}
